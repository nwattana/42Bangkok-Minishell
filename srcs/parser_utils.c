/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaewsae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:59:58 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/21 03:06:20 by lkaewsae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lst_addword(t_list **lst, t_list *word)
{
	t_list			*new;
	static t_list	*last;

	if (lst == NULL || word == NULL)
		return (NULL);
	if (*lst == NULL)
	{
		*lst = word;
		last = word;
	}
	else
	{
		last->next = word;
		last = word;
	}
	return (last);
}

char	*ft_lst_groupword(t_list **lst)
{
	t_list	*tmp;
	char	*str;
	int		i;

	if (lst == NULL || *lst == NULL)
		return (NULL);
	i = ft_lstsize(*lst);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (*lst)
	{
		str[i] = ((char *)(*lst)->content)[0];
		i++;
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp->content);
		tmp->content = NULL;
		free(tmp);
	}
	tmp = NULL;
	str[i] = '\0';
	return (str);
}

t_lexel	*lexel_new(char *str, int type)
{
	t_lexel	*new;

	new = (t_lexel *)malloc(sizeof(t_lexel));
	if (new == NULL)
		return (NULL);
	new->str = str;
	new->type = type;
	return (new);
}

void	parser_init(t_parser *parser)
{
	parser->quote_state = 0;
	parser->lexel_list = NULL;
	parser->tmp_lexel = NULL;
	parser->cur_word = NULL;
	parser->is_char_or_quote = 0;
}
