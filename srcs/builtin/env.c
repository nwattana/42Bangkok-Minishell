/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:00:54 by lkaewsae          #+#    #+#             */
/*   Updated: 2023/02/21 19:10:11 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/my_builtin.h"
#include<stdio.h>

void	ft_env(t_cmd *cmd, t_shell *shell)
{
	char	**env;
	int		i;

	if (cmd->argcount > 1)
	{
		ft_putstr_fd
		(RED"ENV No option and Argument\n"RESET, 2);
		exit (1);
	}
	env = shell->env;
	i = 0;
	while (env[i] != NULL)
	{
		ft_putstr_fd(env[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	exit(0);
}
