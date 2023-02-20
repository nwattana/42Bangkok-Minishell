/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaewsae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:40:24 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/20 21:39:59 by lkaewsae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void		debug_put(void *vtf);
static char	**ft_str2ddup(char **str);
static void	ft_str2dswap(char **a, char **b);

int	put_sort_env(t_shell *shell)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	if (!shell || !shell->env)
		return (1);
	tmp = ft_str2ddup(shell->env);
	while (tmp[i])
	{
		j = i + 1;
		while (tmp[j])
		{
			if (ft_strcmp(tmp[i], tmp[j]) > 0)
			{
				ft_str2dswap(&tmp[i], &tmp[j]);
			}
			j++;
		}
		i++;
	}
	ft_str2diter(tmp, debug_put);
	ft_str2diter(tmp, free);
	free(tmp);
	return (0);
}

void	debug_put(void *vtf)
{
	char	*tmp;

	tmp = (char *)vtf;
	ft_putstr_fd(RED"declare -x "GREEN, 1);
	ft_putstr_fd(tmp, 1);
	ft_putendl_fd(RESET"", 1);
}

static void	ft_str2dswap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static char	**ft_str2ddup(char **str)
{
	char	**ret;
	int		i;

	i = 0;
	while (str[i])
		i++;
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (str[i])
	{
		ret[i] = ft_strdup(str[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
