/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 09:16:47 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/20 01:58:54 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	void	*dup;
	size_t	size;

	if (!s1)
		return (NULL);
	size = ft_strlen(s1) + 1;
	dup = malloc(size);
	if (dup == 0)
		return (0);
	return ((char *)ft_memcpy(dup, s1, size));
}
