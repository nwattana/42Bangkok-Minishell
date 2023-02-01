/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 00:52:01 by nwattana          #+#    #+#             */
/*   Updated: 2022/12/28 22:32:00 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *src, int c)
{
	char	*buff_s;
	size_t	len;
	char	*buff_r;

	len = 0;
	buff_s = (char *)src;
	buff_r = 0;
	c = c % 256;
	c = (unsigned char)c;
	if (c == '\0')
		return ((char *)(src + ft_strlen(src)));
	while (*(buff_s + len) != '\0')
	{
		if (*(buff_s + len) == c)
		{
			buff_r = buff_s + len;
		}
		len++;
	}
	return (buff_r);
}
/*
#include<stdio.h>
int	main(void)
{
	char hello[13] = "Hell Wrld";
	char *hell = ft_strrchr(hello,'o');

	printf("%s\n%s\n",hello,hell);
}*/
