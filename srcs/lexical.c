/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaewsae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:12:14 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/21 01:50:22 by lkaewsae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	lexical_analysis_extend(t_parser *parser, t_shell *shell)
{
	t_lexel	*tmp_lexel;
	t_cmd	*tmp_cmd;
	int		command_start;
	t_list	*tmp_node;
	int		*from_pipe;
	if (tmp_lexel->type == D_REDIR_IN)
		tmp_node = redir_in(tmp_node, &tmp_cmd);
	if (tmp_lexel->type == D_REDIR_OUT)
		tmp_node = redir_out(tmp_node, &tmp_cmd);
	if (tmp_lexel->type == D_PIPE)
	{
		from_pipe = to_pipe(tmp_cmd);
		if (tmp_cmd != NULL)
			ft_lstadd_back(&shell->cmd_list, ft_lstnew(tmp_cmd));
		else
			ft_putstr_fd(RED"Error: PIPE From Nothing is NULL\n"RESET, 2);
		tmp_cmd = create_cmd(NULL);
		tmp_cmd->fd_stdin = from_pipe[0];
		tmp_cmd->pipein = from_pipe;
		tmp_cmd->pipeline_state += 2;
		command_start = 0;
	}
}

void	lexical_analysis(t_parser *parser, t_shell *shell)
{
	t_lexel	*tmp_lexel;
	t_cmd	*tmp_cmd;
	int		command_start;
	t_list	*tmp_node;
	int		*from_pipe;

	tmp_node = parser->lexel_list;
	command_start = 0;
	tmp_cmd = NULL;
	if (tmp_node == NULL)
		return ;
	while (tmp_node)
	{
		tmp_lexel = (t_lexel *)tmp_node->content;
		if (!command_start)
		{
			if (tmp_lexel->type == D_WORD)
			{
				if (!tmp_cmd)
					tmp_cmd = create_cmd(tmp_lexel->str);
				else
					add_command_to_null_cmd(tmp_cmd, tmp_lexel->str);
				command_start = 1;
			}
		}
		else
		{
			if (tmp_lexel->type == D_WORD)
				add_argument(tmp_cmd, tmp_lexel->str);
		}

		if (tmp_node)
			tmp_node = tmp_node->next;
	}
	ft_lstadd_back(&shell->cmd_list, ft_lstnew(tmp_cmd));
	direction_pipeline(shell->cmd_list, shell);
	get_status(shell);
	ft_lstclear(&shell->cmd_list, cmd_clear);
	destroy_parser(parser);
}

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

char	**ft_str2drelloc_free(char **str, int size)
{
	char	**new_str;
	int		i;

	i = 0;
	new_str = ft_calloc(sizeof(char *), size);
	while (i < (size - 10))
	{
		new_str[i] = ft_strdup(str[i]);
		i++;
	}
	ft_str2diter(str, &free);
	free(str);
	return (new_str);
}
// clear here doc file
// and set here doc status to 0
