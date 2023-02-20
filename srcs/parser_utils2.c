/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaewsae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 03:03:16 by lkaewsae          #+#    #+#             */
/*   Updated: 2023/02/21 03:06:15 by lkaewsae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_state_check(char a, t_parser *parser)
{
	if (parser->quote_state == 0 && (a == '\'' || a == '\"'))
	{
		parser->quote_state = a;
		return (1);
	}
	else if (parser->quote_state == a)
	{
		parser->quote_state = 0;
		return (1);
	}
	return (0);
}

void	destroy_parser(t_parser *parser)
{
	if (parser == NULL)
		return ;
	ft_lstclear(&parser->lexel_list, (void *)&lexel_del);
	ft_lstclear(&parser->cur_word, (void *)&free_null);
}

void	lexel_del(t_lexel *lexel)
{
	if (lexel == NULL)
		return ;
	free(((t_lexel *)lexel)->str);
	free(lexel);
}

int	add_lexel(t_parser *parser, int type)
{
	char	*word;

	if (parser == NULL)
		return (1);
	word = ft_lst_groupword(&parser->cur_word);
	if (word == NULL)
		return (1);
	parser->tmp_lexel = lexel_new(word, type);
	if (parser->tmp_lexel == NULL)
		return (1);
	parser->tmp_lst = ft_lstnew(parser->tmp_lexel);
	if (parser->tmp_lst == NULL)
		return (1);
	ft_lstadd_back(&parser->lexel_list, parser->tmp_lst);
	return (0);
}
