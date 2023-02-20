/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:00:54 by lkaewsae          #+#    #+#             */
/*   Updated: 2023/02/20 17:34:40 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/my_builtin.h"
#include<stdio.h>

void ft_env(char **env, t_shell *shell)
{
	int i;
	char *trim;

	trim = ft_strtrim(shell->line, " ");
	if (ft_strcmp(trim, "env") != 0)
	{
		ft_putstr_fd(RED"ENV No option and No pipe or redirection too\n"RESET, 2);
		free(trim);
		exit (1);
	}
	env = shell->env;
	i = 0;
	while(env[i] != NULL)
	{
		ft_putstr_fd(env[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	exit(0);
}
