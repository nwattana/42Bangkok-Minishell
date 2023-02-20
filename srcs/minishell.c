/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaewsae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 20:01:52 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/21 03:46:34 by lkaewsae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*rl_line;
	t_shell		shell;
	t_parser	parser;

	if (argc == 0)
		(void)argv;
	init_shell(&shell, env);
	while (1)
	{
		rl_line = readline(PROMPT);
		if (rl_line == NULL)
			break ;
		parser_init(&parser);
		process_line(rl_line, &shell, &parser);
		if (ft_strlen(rl_line) > 0)
			add_history(rl_line);
		free(rl_line);
	}
	return (0);
}

void	process_line(char *line, t_shell *shell, t_parser *parser)
{
	int	i;

	i = 0;
	shell->line = line;
	while (line[i])
	{
		parser->is_char_or_quote = quote_state_check(line[i], parser);
		i += process_line_extend(i, line[i], shell, parser);
		i++;
	}
	add_lexel(parser, D_WORD);
	if (parser->quote_state != 0)
		ft_putstr_fd(RED"Error: quote not closed\n"RESET, 2);
	lexical_analysis(parser, shell);
}

int	process_line_extend(int i, char line, t_shell *shell, t_parser *parser)
{
	if (parser->quote_state == 0 && ft_isdirection(&line))
	{
		if (ft_lstsize(parser->cur_word) != 0)
			add_lexel(parser, D_WORD);
		add_char(parser, line);
		add_lexel(parser, line);
	}
	else if (parser->quote_state == '\"' && line == '$')
		i += get_dollar(parser, &line, shell);
	else if (parser->quote_state == 0 && line == ' ')
	{
		i += skip_space(&line);
		if (ft_lstsize(parser->cur_word) != 0)
			add_lexel(parser, D_WORD);
	}
	else if (!parser->is_char_or_quote)
	{
		if (line == '$')
			i += get_dollar(parser, &line, shell);
		else
			add_char(parser, line);
	}
	return (i);
}
