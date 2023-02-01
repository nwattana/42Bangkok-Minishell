/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 01:17:40 by nwattana          #+#    #+#             */
/*   Updated: 2022/03/01 09:56:52 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *src1, const void *src2, size_t n)
{
	char	*a1;
	char	*a2;

	a1 = (char *)src1;
	a2 = (char *)src2;
	while (n > 0)
	{
		if (*a1 != *a2)
			return ((unsigned char)*a1 - (unsigned char)*a2);
		n--;
		a1++;
		a2++;
	}
	return (0);
}
/*
#include<stdio.h>
#include<string.h>

int main(void)
{
	char a[6] = "hello";
	char b[6] = "";

	printf("%d\n",ft_memcmp(a,b,3));
	printf("%d\n",ft_memcmp(a,b,5));
}*/
