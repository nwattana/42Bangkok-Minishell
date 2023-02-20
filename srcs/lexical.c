/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaewsae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:12:14 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/21 03:35:19 by lkaewsae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_cmd *lexical_add_cmd(t_lexel *tmp_lexel, t_cmd *tmp_cmd)
{
	if (!tmp_cmd)
		tmp_cmd = create_cmd(tmp_lexel->str);
	else
		add_command_to_null_cmd(tmp_cmd, tmp_lexel->str);
	return (tmp_cmd);
}

void	lexical_mix(t_parser *parser, t_cmd *tmp_cmd, t_shell *shell)
{
	ft_lstadd_back(&shell->cmd_list, ft_lstnew(tmp_cmd));
	direction_pipeline(shell->cmd_list, shell);
	get_status(shell);
	ft_lstclear(&shell->cmd_list, cmd_clear);
	destroy_parser(parser);
}

void	lexical_in_out(t_lexel	*tmp_lexel, t_cmd *tmp_cmd, t_list *tmp_node)
{
	if (tmp_lexel->type == D_REDIR_IN)
		tmp_node = redir_in(tmp_node, &tmp_cmd);
	if (tmp_lexel->type == D_REDIR_OUT)
		tmp_node = redir_out(tmp_node, &tmp_cmd);
}

int	lexical_pipe(t_cmd *tmp_cmd, t_shell *shell)
{
	int	*f_pipe;

	f_pipe = to_pipe(tmp_cmd);
	if (tmp_cmd != NULL)
		ft_lstadd_back(&shell->cmd_list, ft_lstnew(tmp_cmd));
	else
		ft_putstr_fd(RED"Error: PIPE From Nothing is NULL\n"RESET, 2);
	tmp_cmd = create_cmd(NULL);
	tmp_cmd->fd_stdin = f_pipe[0];
	tmp_cmd->pipein = f_pipe;
	tmp_cmd->pipeline_state += 2;
	return (0);
}

void	lexical_analysis(t_parser *parser, t_shell *shell)
{
	t_lexel	*tmp_lexel;
	t_cmd	*tmp_cmd;
	int		command_start;
	t_list	*tmp_node;

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
				tmp_cmd = lexical_add_cmd(tmp_lexel, tmp_cmd);
				command_start = 1;
			}
		}
		else
		{
			if (tmp_lexel->type == D_WORD)
				add_argument(tmp_cmd, tmp_lexel->str);
		}
		lexical_in_out(tmp_lexel, tmp_cmd, tmp_node);
		if (tmp_lexel->type == D_PIPE)
			command_start = lexical_pipe(tmp_cmd, shell);
		if (tmp_node)
			tmp_node = tmp_node->next;
	}
	lexical_mix(parser, tmp_cmd, shell);
}
