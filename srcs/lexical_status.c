/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 02:18:14 by lkaewsae          #+#    #+#             */
/*   Updated: 2023/02/21 15:44:59 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_status(t_shell *sh)
{
	t_list	*tmp;

	if (!sh)
		return (ft_putendl_fd(RED"SHELL is missing?\n"RESET, 2));
	tmp = sh->cmd_list;
	while (tmp && tmp->next)
	{
		tmp = tmp->next;
	}
	sh->last_status = ((t_cmd *)tmp->content)->cmd_pre_exit_status % 256;
}

int	*to_pipe(t_cmd *cmd)
{
	static int	pindex;

	if (cmd == NULL)
		return (NULL);
	pipe(cmd->pipeout);
	if (cmd->fd_stdout != 1)
	{
		close(cmd->pipeout[0]);
	}
	else
	{
		cmd->fd_stdout = cmd->pipeout[1];
		cmd->pipeline_state += 1;
	}
	pindex++;
	return (cmd->pipeout);
}
