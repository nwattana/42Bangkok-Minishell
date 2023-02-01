/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 10:08:33 by nwattana          #+#    #+#             */
/*   Updated: 2023/01/07 10:12:35 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_stack_push(t_stack *sta, t_list *node)
{
	if (!sta)
		return (1);
	ft_lstadd_front(&sta->stack, node);
	if (node)
	{
		sta->isempty = 0;
		sta->size += 1;
	}
	return (0);
}
