/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_pop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 10:12:50 by nwattana          #+#    #+#             */
/*   Updated: 2023/01/07 10:29:38 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_stack_pop(t_stack *sta)
{
	t_list	*pop;

	if (sta->isempty)
		return (NULL);
	else
	{
		pop = sta->stack;
		sta->stack = sta->stack->next;
		pop->next = NULL;
		sta->size -= 1;
		if (sta->size == 0)
			sta->isempty = 1;
	}
	return (pop);
}
