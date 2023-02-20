/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_command_module.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 22:46:51 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/20 14:16:41 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_cmd	*create_cmd(char *str)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->argval = ft_calloc(sizeof(char *), 10);
	if (str != NULL)
	{
		new_cmd->cmd = ft_strdup(str);
		new_cmd->argval[0] = ft_strdup(str);
		new_cmd->argcount = 1;
	}
	else
	{
		new_cmd->cmd = NULL;
		new_cmd->argval[0] = NULL;
		new_cmd->argcount = 0;
	}
	new_cmd->here_doc_status = 0;
	new_cmd->max_arg = 9;
	new_cmd->fd_stdin = 0;
	new_cmd->fd_stdout = 1;
	new_cmd->pipeline_state = 0;
	return (new_cmd);
}

void	add_command_to_null_cmd(t_cmd *cmd, char *str)
{
	cmd->argval[0] = ft_strdup(str);
	cmd->cmd = ft_strdup(str);
	cmd->argcount++;
}

void	cmd_clear(void *vtf_cmd)
{
	int		i;
	t_cmd	*cmd;

	cmd = (t_cmd *)vtf_cmd;
	i = 0;
	if (!cmd)
		return ;
	free(cmd->cmd);
	while (i < cmd->argcount)
	{
		free(cmd->argval[i]);
		i++;
	}
	clear_hd(vtf_cmd);
	free(cmd->argval);
	free(cmd);
	cmd = NULL;
}

t_cmd	*lst_getcmd(t_list *lst)
{
	t_cmd	*cmd;

	if (!lst)
		return (NULL);
	cmd = (t_cmd *)lst->content;
	return (cmd);
}

/// @brief add_argument to argument list however just 
/// alloc for 10 pointer char if execeed it will be realloced
/// @param cmd 
/// @param str 
void	add_argument(t_cmd *cmd, char *str)
{
	if (!cmd)
		return ;
	if (cmd->argcount < cmd->max_arg)
	{
		cmd->argval[cmd->argcount] = ft_strdup(str);
		cmd->argcount++;
	}
	else
	{
		cmd->max_arg += 10;
		cmd->argval = ft_str2drelloc_free(cmd->argval, cmd->max_arg);
		cmd->argval[cmd->argcount] = ft_strdup(str);
		cmd->argcount++;
	}
}
