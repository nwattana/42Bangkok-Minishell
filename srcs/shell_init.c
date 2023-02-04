/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:35:32 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/04 18:00:02 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

 void init_shell(t_shell *shell, char **env)
 {
	if (env)
	{
		clone_env(shell, env);
		ft_str2diter(shell->env, ft_putstr_env); 
	}
 }

void	ft_putstr_env(char *str)
{
	int i;

	i = 0;
	ft_putstr_fd(GREEN"",1);
	while (str[i])
	{
		if (str[i] == '=')
		{
			ft_putstr_fd(RED"",1);
			write(1, str + i, 1);
			ft_putstr_fd(BLUE"",1);
		}
		else
			write(1, str + i, 1);
		i++;
	}
	write(1, "\n", 1);
	ft_putstr_fd(RESET"",1);
}

void    ft_str2diter(char **str, void (*f)(char *))
{
    int i;

    i = 0;
    while (str[i])
    {
        f(str[i]);
        i++;
    }
}

void 	clone_env(t_shell *shell, char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	shell->env = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		shell->env[i] = ft_strdup(env[i]);
		i++;
	}
	shell->env[i] = NULL;
}