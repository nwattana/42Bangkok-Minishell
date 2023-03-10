/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir_out_module.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaewsae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 22:52:43 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/21 03:29:22 by lkaewsae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief To handle redirect out in both mode
/// @param start content == lexer list
/// @param cur_cmd -> t_cmd
/// @return adress of node that be word or error if not found word
t_list	*open_redir_out(t_list *start, t_cmd **cur_cmd, int tmp_type)
{
	t_lexel	*lex;
	int		arrow_count;

	arrow_count = 0;
	while (start)
	{
		lex = (t_lexel *)start->content;
		if (lex->type == tmp_type)
			arrow_count++;
		else if (lex->type == D_WORD)
		{
			if (arrow_count <= 2)
				open_for_write(arrow_count, lex->str, cur_cmd);
			else
				ft_putstr_fd(RED"Redirect ERROR\n"RESET, 2);
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

t_list	*redir_out(t_list *start, t_cmd **cur_cmd)
{
	int		arrow_count;
	int		tmp_type;

	arrow_count = 0;
	if (!cur_cmd || !start)
		return (NULL);
	tmp_type = ((t_lexel *)start->content)->type;
	return (open_redir_out(start, cur_cmd, tmp_type));
}

void	open_for_write(int arrow_count, char *str, t_cmd **curcmd)
{
	if (!curcmd)
		return ;
	if (*curcmd == NULL)
	{
		*curcmd = create_cmd(NULL);
	}
	if ((*curcmd)->fd_stdout != STDOUT_FILENO)
		close((*curcmd)->fd_stdout);
	if (arrow_count == 1)
		(*curcmd)->fd_stdout = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (arrow_count == 2)
		(*curcmd)->fd_stdout = open(str, O_WRONLY | O_CREAT | O_APPEND, 0777);
}
