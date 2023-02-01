/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 00:39:34 by nwattana          #+#    #+#             */
/*   Updated: 2023/01/07 15:26:00 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *src, int c)
{
	char	*buff_s;
	size_t	len;

	len = ft_strlen(src) + 1;
	c = c % 256;
	buff_s = (char *)src;
	while (len > 0)
	{
		if (*buff_s == c)
		{
			return (buff_s);
		}
		buff_s++;
		len--;
	}
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	char Hello[13] = "Hello world";
	char *hell = ft_strchr(Hello, 'w');

	printf("Hello : %s\nHell : %s\n",Hello,hell);
}*/
