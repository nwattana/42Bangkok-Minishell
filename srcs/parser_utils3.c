/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaewsae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 03:04:18 by lkaewsae          #+#    #+#             */
/*   Updated: 2023/02/21 03:06:12 by lkaewsae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (i > 0)
		return (i - 1);
	return (i);
}

int	ft_isdirection(char *c)
{
	if (c == NULL)
		return (0);
	if (*c == '>' || *c == '<' || *c == '|')
		return (1);
	return (0);
}

int	add_char(t_parser *parser, char c)
{
	t_list	*new;

	if (!parser)
		return (1);
	new = ft_lst_newchar(c);
	if (new == NULL)
		return (1);
	ft_lst_addword(&(parser->cur_word), new);
	return (0);
}

t_list	*ft_lst_newchar(char c)
{
	t_list	*new;
	char	*str;

	str = (char *)malloc(sizeof(char) * 2);
	if (str == NULL)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = str;
	new->next = NULL;
	return (new);
}
