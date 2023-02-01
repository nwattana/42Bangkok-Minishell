/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 02:23:22 by nwattana          #+#    #+#             */
/*   Updated: 2022/03/12 15:03:07 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*res;
	size_t	iter;
	size_t	total;

	iter = 0;
	total = size * count;
	res = malloc(total);
	if (!res)
		return (0);
	while (iter < total)
	{
		*(res + iter) = '\0';
		iter++;
	}
	return (res);
}
