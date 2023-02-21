/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaewsae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 20:01:52 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/21 16:37:01 by lkaewsae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern t_shell	*g_shell;

int	main(int argc, char **argv, char **env)
{
	char		*rl_line;
	t_shell		shell;

	g_shell = &shell;
	set_signal(g_shell);
	if (argc == 0)
		(void)argv;
	init_shell(&shell, env);
	while (1)
	{
		rl_line = readline(PROMPT);
		if (rl_line == NULL)
			break ;
		shell.line = rl_line;
		process_line(rl_line, &shell);
		if (ft_strlen(rl_line) > 0)
			add_history(rl_line);
		free(rl_line);
	}
	univesal_clear(g_shell);
	ft_putstr_fd(PROMPT"Exit\n", 1);
	return (0);
}

void	process_line(char *line, t_shell *shell)
{
	t_parser	parser;
	int			i;

	i = 0;
	parser_init(&parser);
	while (line[i])
	{
		parser.is_char_or_quote = quote_state_check(line[i], &parser);
		process_line_ex(line, &i, &parser, shell);
		i++;
	}
	add_lexel(&parser, D_WORD);
	pre_lexical_analysis(&parser, shell);
}
