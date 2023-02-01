/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 17:55:42 by nwattana          #+#    #+#             */
/*   Updated: 2022/03/06 18:09:51 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int		i;
	unsigned int		len;

	if (!(s == NULL || f == NULL))
	{
		len = 0;
		i = 0;
		while (s[len] != '\0')
			len++;
		while (i < len)
		{
			f(i, (char *)(s + i));
			i++;
		}
	}
}
