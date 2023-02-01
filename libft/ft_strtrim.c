/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 02:16:25 by nwattana          #+#    #+#             */
/*   Updated: 2022/03/12 17:35:17 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (*(set + i) == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	find_allocsize(char const *s1, char const *set)
{
	size_t	found_count;
	size_t	s_len;
	size_t	i;

	s_len = ft_strlen(s1);
	found_count = 0;
	i = 0;
	while (*(s1 + i) != '\0' && in_set(*(s1 + i), set))
	{
		found_count++;
		i++;
	}
	if (found_count == s_len)
		return (0);
	i = s_len - 1;
	while (i > 0 && in_set(*(s1 + i), set))
	{
		found_count++;
		i--;
	}
	return (s_len - found_count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	iter1;
	size_t	len_s;
	size_t	alloc_size;

	len_s = ft_strlen(s1);
	iter1 = 0;
	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return ((char *)(s1));
	alloc_size = find_allocsize(s1, set) + 1;
	res = (char *)malloc(sizeof(char) * alloc_size);
	if (!res)
		return (NULL);
	while (iter1 < len_s && in_set(*(s1 + iter1), set))
		iter1++;
	if (alloc_size == 1)
		*res = '\0';
	else
		ft_strlcpy(res, s1 + iter1, alloc_size);
	return (res);
}
