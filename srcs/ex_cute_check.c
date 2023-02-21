/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cute_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaewsae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 00:47:05 by lkaewsae          #+#    #+#             */
/*   Updated: 2023/02/21 18:17:41 by lkaewsae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	iscmd_inbuilt_in(t_cmd *cmd, t_shell *shell, int pid)
{
	if (!pid && ft_strcmp(cmd->cmd, "echo") == 0)
		ft_echo(cmd);
	else if (!pid && ft_strcmp(cmd->cmd, "env") == 0)
		ft_env(shell->env, shell);
	else if (!pid && ft_strcmp(cmd->cmd, "pwd") == 0)
		ft_pwd(shell);
	else if (pid && ft_strcmp(cmd->cmd, "export") == 0)
		ft_export(cmd, shell);
	else if (pid && ft_strcmp(cmd->cmd, "unset") == 0)
		ft_unset(cmd, shell);
	else if (pid && ft_strcmp(cmd->cmd, "cd") == 0)
		ft_cd(cmd, shell);
	else if (pid && ft_strcmp(cmd->cmd, "exit") == 0)
		ft_exit(cmd, shell);
	else
		return (check_isparent_cmd(cmd->cmd));
	return (0);
}

int	check_isparent_cmd(char *cmd)
{
	if (ft_strcmp(cmd, "export") == 0)
		return (0);
	if (ft_strcmp(cmd, "unset") == 0)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0)
		return (0);
	if (ft_strcmp(cmd, "exit") == 0)
		return (0);
	return (1);
}

char	*check_access(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	int		i;

	i = 0;
	path = cmd->cmd;
	if (access(path, F_OK) == 0)
		return (path);
	path_update(shell);
	if (!shell->path)
		return (NULL);
	while (shell->path[i])
	{
		path = ft_strjoin(shell->path[i], "/");
		path = ft_strappend(path, cmd->cmd);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
		free(path);
	}
	return (NULL);
}
