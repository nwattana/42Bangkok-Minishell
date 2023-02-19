/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:25:51 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/20 02:43:28 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
# include "../inc/debug.h"

int	check_isparent_cmd(char *cmd);

int		direction_pipeline(t_list *cmd_list, t_shell *shell)
{
	int		stdfd[2];
	t_list	*tmp;
	int		pid;
	t_cmd	*cmd;

	stdfd[0] = dup(STDIN_FILENO);
	stdfd[1] = dup(STDOUT_FILENO);
	tmp = cmd_list;
	while (tmp)
	{
		cmd = (t_cmd *)tmp->content;
		pid = fork();
		// cmd->fd had change before here
		// closing pipe
		if (pid == 0)
		{
			// child program
			close_pipe(cmd, stdfd);
			if (iscmd_inbuilt_in(cmd, shell, pid) != 0)
			{
				ex_cute(cmd, shell);
			}
			exit(0);
		}
		else
		{
			if (cmd->pipeline_state & 1)
				dup2(cmd->pipeout[0], STDIN_FILENO);
			iscmd_inbuilt_in(cmd, shell, pid);
			close(cmd->pipeout[1]);
			waitpid(pid, NULL, 0);
			// forgot what is this ??
			// V
			// if (cmd->fd_stdin != 0)
			// 	close(cmd->fd_stdin);
			tmp = tmp->next;
		}
	}

	// return STDFILE to Normal
	dup2(stdfd[0], STDIN_FILENO);
	dup2(stdfd[1], STDOUT_FILENO);
	return (0);
}

// pipein [][] from previose cmd <- current cmd command will read from read end of this pipe
// pipeout [][] from currebt cmd <- current cmd will write to write to write end of this pipe
// pipeline_state -> readfrom pipe += 1 write to pipe += 2
// @debug a lot of bug below
void close_pipe(t_cmd *cmd, int *std)
{
	//cmd_dump(cmd);
	if (cmd->pipeline_state & 2)
	{
		//dprintf(2,CYAN"Close pipe in : write end {%d}\n", cmd->pipein[1]);
		close(cmd->pipein[1]);
	}
	// check
	if (cmd->pipeline_state & 1)
	{
		//dprintf(2,CYAN"Close pipe out : read end {%d}\n", cmd->pipeout[0]);
		close(cmd->pipeout[0]);
	}

	/// 
	if (cmd->fd_stdin == 0)
	{
		ft_putstr_fd("", 1);
	}
	else if (cmd->fd_stdin < 0)
	{
		//ft_putstr_fd(RED"FILE IN NOT FOUND : ERROR\n"RESET, 2);
		exit(0);
	}
	else
	{
		//dprintf(2,WHITE"Copy stdin of file  TO  fd 0 cmd "RED"{%s}"WHITE" in %d\n", cmd->cmd, cmd->fd_stdin);
		dup2(cmd->fd_stdin, STDIN_FILENO);
	}

	// @debug STDOUT -> direction
	if (cmd->fd_stdout == 1)
	{
		//dprintf(2,WHITE"RESET STDOUT for cmd "RED"{%s}"WHITE" in %d\n", cmd->cmd, cmd->fd_stdout);
		dup2(std[1], STDOUT_FILENO);
	}
	else if (cmd->fd_stdout < 0)
	{
		//ft_putstr_fd(RED"FILE OUT NOT FOUND : ERROR\n"RESET, 2);
		exit(0);
	}
	else
	{
		//dprintf(2,WHITE"Open PIPEOUT of cmd "RED"{%s}"WHITE" in %d\n", cmd->cmd, cmd->pipeout[1]);
		dup2(cmd->fd_stdout, STDOUT_FILENO);
	}
}


int		iscmd_inbuilt_in(t_cmd *cmd, t_shell *shell, int pid)
{
	if (!pid && ft_strcmp(cmd->cmd, "echo") == 0)
		ft_echo(cmd);
	else if (!pid && ft_strcmp(cmd->cmd, "env") == 0)
		ft_env(shell->env, shell);
	else if (!pid && ft_strcmp(cmd->cmd, "pwd") == 0)
		ft_pwd(shell);
	// pid = 0 but is command
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
	path_update(shell);
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

void	path_update(t_shell *shell)
{
	char	*tmp;

	tmp = get_env_from_key("PATH", shell);
	ft_str2diter(shell->path, free);
	shell->path = ft_split(tmp, ':');
}

void	ex_cute(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	path = check_access(cmd, shell);
	if (path == NULL)
	{
		ft_putstr_fd(RED"COMMAND: NOT FOUND!!\n"RESET, 2);
		exit(1);
	}
	dprintf(2, "Execve with %s\n", path);
	if (execve(path, cmd->argval, NULL) == -1)
	{
		ft_putstr_fd(RED"ERROR: Command Execve error\n",2);
		exit(1);
	}
}
