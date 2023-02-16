/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:46:57 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/15 21:32:14 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/debug.h"

void    execute(t_shell *shell)
{
	t_cmd   *tmp_cmd;
	t_list  *cmd_node;
	int     pid;

	cmd_node = shell->cmd_list;
	while (cmd_node)
	{
		tmp_cmd = lst_getcmd(cmd_node);
		dup2(tmp_cmd->fd_stdin, STDIN_FILENO);
		dup2(tmp_cmd->fd_stdout, STDOUT_FILENO);
		pid = fork();
		if (pid == 0)
		{
			child_process(tmp_cmd, shell);
			exit(0);
		}
		else
		{
			waitpid(pid, &(tmp_cmd->cmd_status), 0);

			// close file
			if (tmp_cmd->fd_stdin != STDIN_FILENO)
				close(tmp_cmd->fd_stdin);
			if (tmp_cmd->fd_stdin != STDOUT_FILENO)
				close(tmp_cmd->fd_stdout);
			if (tmp_cmd->here_doc_status == 1)
			{
				clear_hd(tmp_cmd);
			}
			
			dup2(shell->sh_stdout, STDOUT_FILENO);
			dup2(shell->sh_stdin, STDIN_FILENO);
			cmd_node = cmd_node->next;
		}
	}
	dprintf(2, "Exit %d\n", tmp_cmd->cmd_status);
	ft_lstclear(&shell->cmd_list, free);
	shell->cmd_list = NULL;
}

void    child_process(t_cmd *cmd, t_shell *shell)
{
	int     iter;
	char    *real_cmd;

	iter = 0;
	real_cmd = check_access(cmd, shell);
	if (real_cmd == NULL)
	{
		ft_debug_greenstr_nl("Command not found");
		exit(1);
		return ;
	}
	execve(real_cmd, cmd->argval, NULL);
	exit(1);
}

char    *check_access(t_cmd *cmd, t_shell *shell)
{
	char    *path;
	int     i;

	i = 0;
	path = cmd->cmd;
	if (access(path,F_OK) == 0)
	{
		return (path);
	}
	while (shell->path[i])
	{
		path = ft_strjoin(shell->path[i], "/");
		path = ft_strappend(path, cmd->cmd);
		if (access(path , F_OK) == 0)
			return (path);
		i++;
		free(path);
	}
	return (NULL);
}