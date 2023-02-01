/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 01:30:51 by nwattana          #+#    #+#             */
/*   Updated: 2022/03/12 14:11:29 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (len > s_len)
		len = s_len ;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (0);
	if (start < s_len)
	{
		ft_strlcpy(res, s + start, len + 1);
	}
	else
		*res = '\0';
	return (res);
}
