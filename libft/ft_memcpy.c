/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 04:12:02 by nwattana          #+#    #+#             */
/*   Updated: 2022/03/12 16:39:18 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*buff_d;
	unsigned char	*buff_s;

	buff_d = (unsigned char *)dst;
	buff_s = (unsigned char *)src;
	while (n--)
	{
		*buff_d++ = *buff_s++;
	}
	return (dst);
}
