/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:12:14 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/21 15:57:40 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern t_shell	*g_shell;
void	lexana_if_word(t_lexana *lexana);
void	lexana_if_dir(t_lexana *lexana);
void	lexana_if_pipe(t_lexana *lexana, t_shell *shell);
void	cmd_dump(void *content);

void	lexical_analysis(t_parser *parser, t_shell *shell)
{
	t_lexana	lexana;

	lexana.tmp_node = parser->lexel_list;
	lexana.command_start = 0;
	lexana.tmp_cmd = NULL;
	if (lexana.tmp_node == NULL)
		return ;
	while (lexana.tmp_node)
	{
		lexana.tmp_lexel = (t_lexel *)lexana.tmp_node->content;
		lexana_if_word(&lexana);
		lexana_if_dir(&lexana);
		lexana_if_pipe(&lexana, shell);
		if (lexana.tmp_node)
			lexana.tmp_node = lexana.tmp_node->next;
	}
	if (lexana.tmp_cmd == NULL)
	{
		ft_putstr_fd(TO_BADUSER""RED"Single Meta char ?\n"RESET, 2);
		return ;
	}
	ft_lstadd_back(&shell->cmd_list, ft_lstnew(lexana.tmp_cmd));
	direction_pipeline(shell->cmd_list, shell);
	get_status(shell);
	ft_lstclear(&shell->cmd_list, cmd_clear);
}

void	lexana_if_word(t_lexana *lexana)
{
	if (!lexana->command_start)
	{
		if (lexana->tmp_lexel->type == D_WORD)
		{
			if (!lexana->tmp_cmd)
				lexana->tmp_cmd = create_cmd(lexana->tmp_lexel->str);
			else
				add_command_to_null_cmd(lexana->tmp_cmd, \
					lexana->tmp_lexel->str);
			lexana->command_start = 1;
		}
	}
	else
	{
		if (lexana->tmp_lexel->type == D_WORD)
		{
			add_argument(lexana->tmp_cmd, \
				lexana->tmp_lexel->str);
		}
	}
}

void	lexana_if_dir(t_lexana *lexana)
{
	if (lexana->tmp_lexel->type == D_REDIR_IN)
	{
		lexana->tmp_node = redir_in(lexana->tmp_node, \
			&lexana->tmp_cmd);
	}
	if (lexana->tmp_lexel->type == D_REDIR_OUT)
	{
		lexana->tmp_node = redir_out(lexana->tmp_node, \
			&lexana->tmp_cmd);
	}
}

void	lexana_if_pipe(t_lexana *lexana, t_shell *shell)
{
	if (lexana->tmp_lexel->type == D_PIPE)
	{
		if (lexana->tmp_cmd != NULL)
		{
			lexana->from_pipe = to_pipe(lexana->tmp_cmd);
			ft_lstadd_back(&shell->cmd_list, ft_lstnew(lexana->tmp_cmd));
		}
		else
		{
			return ((void)ft_putstr_fd(RED"Error: PIPE From"\
			" Nothing is NULL\n"RESET, 2));
		}
		lexana->tmp_cmd = create_cmd(NULL);
		lexana->tmp_cmd->fd_stdin = lexana->from_pipe[0];
		lexana->tmp_cmd->pipein = lexana->from_pipe;
		lexana->tmp_cmd->pipeline_state += 2;
		lexana->command_start = 0;
	}
}
