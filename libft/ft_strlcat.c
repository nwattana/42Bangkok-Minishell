/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 23:58:54 by nwattana          #+#    #+#             */
/*   Updated: 2022/03/02 14:46:59 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *src, size_t len)
{
	size_t		add_n;
	size_t		len_d;
	size_t		len_s;
	size_t		total;

	len_d = ft_strlen(dst);
	len_s = ft_strlen(src);
	total = ft_strlen(dst) + ft_strlen(src);
	add_n = len - len_d - 1;
	if (len_d >= len)
	{
		return (len + len_s);
	}
	while (*src != '\0' && add_n > 0)
	{
		*(dst + len_d) = *(src++);
		add_n--;
		len_d++;
	}
	*(dst + len_d) = '\0';
	return (total);
}
