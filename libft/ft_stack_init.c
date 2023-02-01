/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 10:03:45 by nwattana          #+#    #+#             */
/*   Updated: 2023/01/07 10:08:14 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack	*ft_stack_init(t_list *node)
{
	t_stack		*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	if (!node)
	{
		stack->isempty = 1;
		stack->size = 0;
		stack->stack = NULL;
	}
	else
	{
		stack->isempty = 0;
		stack->size = 1;
		stack->stack = node;
	}
	return (stack);
}
