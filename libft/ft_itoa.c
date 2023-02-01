/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:02:57 by nwattana          #+#    #+#             */
/*   Updated: 2022/03/12 17:11:06 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countdigit(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		++count;
	}
	return (count);
}

static int	ft_check_flag(int *n, char *s)
{
	int	i;
	int	c;

	c = *n;
	i = 0;
	if (c < 0)
	{
		s[0] = '-';
		i++;
		c = -c;
	}
	*n = c;
	return (i);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		digit;
	int		i;

	i = 0;
	digit = ft_countdigit(n);
	res = (char *)malloc((digit + 2) * sizeof(char));
	if (!res)
		return (0);
	if (n == -2147483648)
	{
		ft_strlcpy(res, "-2147483648", digit + 2);
		return (res);
	}
	i = ft_check_flag(&n, res);
	*(res + digit + i) = '\0';
	while (digit > 0)
	{
		*(res + i + digit - 1) = (n % 10) + '0';
		n = n / 10;
		digit--;
	}
	return (res);
}
