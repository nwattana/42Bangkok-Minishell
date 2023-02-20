/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 20:01:52 by nwattana          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/21 03:46:34 by lkaewsae         ###   ########.fr       */
=======
/*   Updated: 2023/02/21 01:54:46 by nwattana         ###   ########.fr       */
>>>>>>> 165e408bb7d52839f2400a2186bf002b11fa8ad5
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern	t_shell	*G_SHELL;

int main(int argc, char **argv, char **env)
{
	char		*rl_line;
	t_shell		shell;
	t_parser	parser;

	G_SHELL = &shell;
	if (argc == 0)
		(void)argv;
	init_shell(&shell, env);
	while (1)
	{
		rl_line = readline(PROMPT);
		if (rl_line == NULL)
<<<<<<< HEAD
			break ;
		parser_init(&parser);
		process_line(rl_line, &shell, &parser);
=======
		{
			ft_putstr_fd(PROMPT"exit", 0);
			univesal_clear(&shell);
			break;
		}
		process_line(rl_line, &shell);
>>>>>>> 165e408bb7d52839f2400a2186bf002b11fa8ad5
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
