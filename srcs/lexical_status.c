/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaewsae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 02:18:14 by lkaewsae          #+#    #+#             */
/*   Updated: 2023/02/21 02:19:02 by lkaewsae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_status(t_shell *sh)
{
	t_list	*tmp;

	if (!sh)
		return (ft_putendl_fd(RED"SHELL is missing?"RESET, 2));
	tmp = sh->cmd_list;
	while (tmp && tmp->next)
	{
		tmp = tmp->next;
	}
	sh->last_status = ((t_cmd *)tmp->content)->cmd_pre_exit_status % 256;
}

/// @brief  add current command direction out
/// @param cmd
int	*to_pipe(t_cmd *cmd)
{
	static int	pindex;

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
