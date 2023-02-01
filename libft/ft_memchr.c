/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 01:33:02 by nwattana          #+#    #+#             */
/*   Updated: 2022/03/12 17:35:38 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t len)
{
	unsigned char	*a1;
	size_t			i;

	a1 = (unsigned char *)src;
	i = 0;
	c = c % 256;
	c = (unsigned char)c;
	while (i < len)
	{
		if (*(a1 + i) == c)
		{
			return (a1 + i);
		}
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%s",(char *)ft_memchr("Hello", 'l',4));
}*/
