/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 10:21:17 by nwattana          #+#    #+#             */
/*   Updated: 2023/01/07 10:31:11 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_stack_clear(t_stack *sta, void (*del)(void *))
{
	if (!sta)
		return (1);
	ft_lstclear(&sta->stack, del);
	free(sta);
	sta = NULL;
	return (0);
}
