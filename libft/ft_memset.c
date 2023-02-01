/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 00:39:36 by nwattana          #+#    #+#             */
/*   Updated: 2022/03/01 03:10:07 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char		*buff;

	buff = (unsigned char *)b;
	while (len-- > 0)
	{
		*buff++ = c;
	}
	return (b);
}
