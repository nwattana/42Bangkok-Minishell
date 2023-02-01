/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 04:44:14 by nwattana          #+#    #+#             */
/*   Updated: 2022/03/12 16:29:07 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*buff_s;
	char	*buff_d;

	buff_d = (char *)dst;
	buff_s = (char *)src;
	if (dst == NULL && src == NULL)
		return (dst);
	if (buff_d < buff_s)
	{
		while (n--)
		{
			*buff_d++ = *buff_s++;
		}
	}
	else
	{
		buff_d += n - 1;
		buff_s += n - 1;
		while (n--)
		{
			*buff_d-- = *buff_s--;
		}
	}
	return (dst);
}
