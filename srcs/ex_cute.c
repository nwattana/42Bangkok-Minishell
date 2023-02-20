/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaewsae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:25:51 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/21 01:08:55 by lkaewsae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	parent_process(t_cmd *cmd, int pid, t_shell *shell)
{
	if (cmd->pipeline_state & 1)
		dup2(cmd->pipeout[0], STDIN_FILENO);
	iscmd_inbuilt_in(cmd, shell, pid);
	close(cmd->pipeout[1]);
	waitpid(pid, &cmd->cmd_exit_status, 0);
	cmd->cmd_pre_exit_status = WEXITSTATUS(cmd->cmd_exit_status);
}

int	direction_pipeline(t_list *cmd_list, t_shell *shell)
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
		if (pid == 0)
		{
			close_pipe(cmd, stdfd);
			if (iscmd_inbuilt_in(cmd, shell, pid) != 0)
				ex_cute(cmd, shell);
			exit(1);
		}
		parent_process(cmd, pid, shell);
		tmp = tmp->next;
	}
	dup2(stdfd[0], STDIN_FILENO);
	dup2(stdfd[1], STDOUT_FILENO);
	return (0);
}

// pipein [][] from previose cmd
//<- current cmd command will read from read end of this pipe
// pipeout [][] from currebt cmd
//<- current cmd will write to write to write end of this pipe
// pipeline_state
//-> readfrom pipe += 1 write to pipe += 2
// @debug a lot of bug below
void	close_pipe(t_cmd *cmd, int *std)
{
	if (cmd->pipeline_state & 2)
		close(cmd->pipein[1]);
	if (cmd->pipeline_state & 1)
		close(cmd->pipeout[0]);
	if (cmd->fd_stdin == 0)
		ft_putstr_fd("", 1);
	else if (cmd->fd_stdin < 0)
		exit(0);
	else
		dup2(cmd->fd_stdin, STDIN_FILENO);
	if (cmd->fd_stdout == 1)
		dup2(std[1], STDOUT_FILENO);
	else if (cmd->fd_stdout < 0)
		exit(0);
	else
		dup2(cmd->fd_stdout, STDOUT_FILENO);
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
		ft_putstr_fd(RED"MINISHELL: "RESET, 2);
		ft_putstr_fd(cmd->argval[0], 2);
		ft_putstr_fd(RED": COMMAND: NOT FOUND!!: ", 2);
		ft_putendl_fd(RESET"", 2);
		cmd->cmd_pre_exit_status = 127;
		exit(127);
	}
	if (execve(path, cmd->argval, NULL) == -1)
	{
		ft_putstr_fd(RED"ERROR: Command Execve error\n", 2);
		exit(1);
	}
}
