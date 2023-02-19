/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:01:18 by lkaewsae          #+#    #+#             */
/*   Updated: 2023/02/19 22:24:11 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtin.h"

static int	set_cancle(t_cmd *cmd, t_shell *shell);

int	ft_unset(t_cmd *cmd, t_shell *shell)
{
	int		len;
	char	**newenv;
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	len = ft_str2dlen(shell->env) - set_cancle(cmd, shell);
	newenv = malloc(sizeof(char *) * (len + 1));
	while (shell->env[i])
	{
		if (shell->env[i][0] == '\n')
		{
			free(shell->env[i]);
		}
		else
		{
			newenv[j] = shell->env[i];
			j++;
		}
		i++;
	}
	newenv[j] = NULL;
	free(shell->env);
	shell->env = newenv;
	return (0);
}

int		ft_str2dlen(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{	
		i++;
	}
	return (i);
}

static int	set_cancle(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	j;
	int	newlen;
	int	arglen;
	
	newlen = 0;
	i = 1;
	while (cmd->argval[i])
	{
		j = 0;
		arglen = ft_strlen(cmd->argval[i]);
		while (shell->env[j])
		{
			if (ft_strncmp(cmd->argval[i], shell->env[j], arglen) == 0)
			{
				newlen++;
				shell->env[j][0]='\n';
				break ; 
			}
			j++;
		}
		i++;
	}
	// dprintf(2, CYAN"%d\n", newlen);
	return (newlen);
}