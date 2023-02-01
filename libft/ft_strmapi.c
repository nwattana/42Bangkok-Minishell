/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 18:10:06 by nwattana          #+#    #+#             */
/*   Updated: 2022/03/12 14:20:29 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	unsigned int	len;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (0);
	i = 0;
	len = 0;
	while (*(s + len) != '\0')
		len++;
	res = malloc(sizeof(char) * len + 1);
	if (!res)
		return (0);
	while (*(s + i) != '\0')
	{
		res[i] = f(i, *(s + i));
		i++;
	}
	res[i] = '\0';
	return (res);
}
