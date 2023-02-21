/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line_extern.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:47:30 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/21 14:33:51 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	pre_lexical_analysis(t_parser *parser, t_shell *shell)
{
	if (parser->quote_state != 0)
		ft_putstr_fd(RED"Error: quote not closed\n"RESET,2);
	else
		lexical_analysis(parser, shell);
	destroy_parser(parser);
}

void	process_line_ex(char *line, int *i, t_parser *parser, t_shell *shell)
{
	if (parser->quote_state == 0 && ft_isdirection(line + *i))
	{
		if (ft_lstsize(parser->cur_word) != 0)
			add_lexel(parser, D_WORD);
		add_char(parser, line[*i]);
		add_lexel(parser, line[*i]);
	}
	else if (parser->quote_state == '\"' && line[*i] == '$')
		*i += get_dollar(parser, line + *i, shell);
	else if (parser->quote_state == 0 && line[*i] == ' ')
	{
		*i += skip_space(line + *i);
		if (ft_lstsize(parser->cur_word) != 0)
			add_lexel(parser, D_WORD);
	}
	else if (!parser->is_char_or_quote)
	{
		if (line[*i] == '$')
			*i += get_dollar(parser, line + *i, shell);
		else
			add_char(parser, line[*i]);
	}
}