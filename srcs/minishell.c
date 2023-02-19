/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 20:01:52 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/19 12:04:12 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/debug.h"

void ft_env(char **env)
{
	int i = 0;
	while(env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

int main(int argc, char **argv, char **env)
{
	char		*rl_line;
	t_shell		shell;

	if (argc == 0)
		(void)argv;
	init_shell(&shell, env);
	while (1)
	{
		rl_line = readline(PROMPT);
		if (rl_line == NULL)
			break;
		process_line(rl_line, &shell);
		if (ft_strlen(rl_line) > 0)
			add_history(line);
		free(rl_line);
	}
	// @skip no need to handle here it will update in future
	if (rl_line)
		free(rl_line);
	return (0);
}

void process_line(char *line, t_shell *shell)
{
	t_parser	parser;
	int			i;

	i = 0;
	parser_init(&parser);
	while (line[i])
	{
		// tmp = show current is quote validate as quote or char
		parser.is_char_or_quote = quote_state_check(line[i], &parser);
		if (parser.quote_state == 0 && ft_isdirection(&line[i]))
		{
			if (ft_lstsize(parser.cur_word) != 0)
			{
				add_lexel(&parser, D_WORD);
			}
			add_char(&parser, line[i]);
			add_lexel(&parser, line[i]);
		}
		else if (parser.quote_state == '\"' && line[i] == '$')
		{
			// expand $env and join to current word
			i += get_dollar(&parser, &line[i]);
		}
		else if (parser.quote_state == 0 && line[i] == ' ')
		{
			i += skip_space(&line[i]);

			/// @brief adding current group of word to lexer element list
			if (ft_lstsize(parser.cur_word) != 0)
			{
				// return error statement
				add_lexel(&parser, D_WORD);
			}
		}
		else if (!parser.is_char_or_quote)
		{
			if (line[i] == '$')
			{
				i += get_dollar(&parser, &line[i]);
			}
			else
				add_char(&parser, line[i]);
		}
		i++;
	}
	add_lexel(&parser, D_WORD);
	// // @debug zone
	//  debug_lstnext_show(parser.lexel_list);
	//  dump_lexel_list(parser.lexel_list);

	if (parser.quote_state != 0)
		dprintf(2,RED"Error: quote not closed\n"RESET);
	// @lexical analysis
	lexical_analysis(&parser, shell);

	
	//@brif Note to delete parser element
	//destroy_parser(&parser);
}
