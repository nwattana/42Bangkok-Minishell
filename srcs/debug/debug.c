/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:32:18 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/04 17:34:10 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/debug.h"

void	debug_lexel_print(t_lexel *lexel)
{
	if (lexel == NULL)
		return ;
	printf("lexel: %s, type: %d\n", lexel->str, lexel->type);
}

void dump_lexel_list(t_list *head)
{
	t_list *tmp;

	ft_lstiter(head, (void *)debug_lexel_print);
	tmp = head;
	while (tmp)
	{
		if (((t_lexel *)tmp->content)->type == 0)
			printf("\"%s\"-> ", ((t_lexel *)tmp->content)->str);
		else
			printf("%s -> ", ((t_lexel *)tmp->content)->str);
		tmp = tmp->next;
	}
	tmp = head;
	printf("\n");
	while (tmp)
	{
		printf("%d -> ", ((t_lexel *)tmp->content)->type);
		tmp = tmp->next;
	}
}

void	debug_lstnext_show(t_list *head)
{
	t_list *tmp;

	tmp = head;
	while (tmp)
	{
		printf("%p -> ", tmp);
		tmp = tmp->next;
	}
	printf("NULL\n");
}