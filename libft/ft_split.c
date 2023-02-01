/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 02:41:34 by nwattana          #+#    #+#             */
/*   Updated: 2022/03/12 17:07:38 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_len(const char *str, char chr)
{
	int	word_len;

	word_len = 0;
	while (str[word_len] != '\0' && str[word_len] != chr)
		word_len++;
	return (word_len);
}

static int	ft_count_word(const char *str, char chr)
{
	int	word;

	word = 0;
	while (*str)
	{
		while (*str && *str == chr)
			str++;
		if (*str && *str != chr)
			word++;
		while (*str && *str != chr)
			str++;
	}
	return (word);
}

static char	*ft_getword(const char *src, int len, char chr)
{
	char	*res;
	int		i;

	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (*src && *src != chr)
		res[i++] = *src++;
	res[i] = '\0';
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		word;
	int		len;
	int		i;

	if (s == NULL)
		return (NULL);
	word = ft_count_word(s, c);
	res = (char **)malloc(sizeof(char *) * (word + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < word)
	{
		while (*s && *s == c)
			s++;
		len = ft_word_len(s, c);
		res[i] = ft_getword(s, len, c);
		while (*s && *s != c)
			s++;
		i++;
	}
	res[i] = 0;
	return (res);
}
