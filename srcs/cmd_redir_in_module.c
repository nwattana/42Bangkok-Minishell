/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir_in_module.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaewsae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 22:56:06 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/21 03:29:49 by lkaewsae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	*open_redir_in(t_list *start, t_cmd **cur_cmd, int tmp_type)
{
	int		arrow_count;
	t_lexel	*lex;

	arrow_count = 0;
	while (start)
	{
		lex = ((t_lexel *)start->content);
		if (lex->type == tmp_type)
			arrow_count++;
		else if (lex->type == D_WORD)
		{
			open_for_read(arrow_count, lex->str, cur_cmd);
			break ;
		}
		else
		{
			ft_putstr_fd(RED"Incomplete Redirect\n"RESET, 2);
			return (start->next);
		}
		start = start->next;
	}
	return (start);
}

t_list	*redir_in(t_list *start, t_cmd **cur_cmd)
{
	int		tmp_type;
	int		arrow_count;

	arrow_count = 0;
	if (!cur_cmd || !start)
		return (start);
	tmp_type = ((t_lexel *)start->content)->type;
	return (open_redir_in(start, cur_cmd, tmp_type));
}

/// @brief To Handle heredoc and redirect in open
/// file readmode and give it to cmd->fdstdin
/// @param arrow_count
/// @param str
/// @param curcmd

int	open_heredoc(char *str, t_cmd **curcmd)
{
	char	*tmp_hd;
	int		file_to_open;

	(*curcmd)->heredoc_filename = hd_name(str);
	(*curcmd)->here_doc_status = 1;
	tmp_hd = get_here_doc(str);
	file_to_open = open((*curcmd)->heredoc_filename, \
	O_WRONLY | O_CREAT | O_TRUNC, \
	0777);
	write(file_to_open, tmp_hd, ft_strlen(tmp_hd));
	close(file_to_open);
	file_to_open = open((*curcmd)->heredoc_filename, O_RDONLY);
	return (file_to_open);
}

void	open_for_read(int arrow_count, char *str, t_cmd **curcmd)
{
	if (!curcmd)
		return ;
	if (!*curcmd)
		*curcmd = create_cmd(NULL);
	if ((*curcmd)->fd_stdin != STDIN_FILENO)
	{
		clear_hd((*curcmd));
		close ((*curcmd)->fd_stdin);
	}
	if (arrow_count == 1)
		(*curcmd)->fd_stdin = open(str, O_RDONLY, 0777);
	else if (arrow_count == 2)
	{
		(*curcmd)->fd_stdin = open_heredoc(str, curcmd);
	}
	else
		(*curcmd)->cmd_pre_exit_status = 1;
}
