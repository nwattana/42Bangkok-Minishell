/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:12:14 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/13 23:48:06 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"
# include "../inc/debug.h"


void    add_command_to_null_cmd(t_cmd *cmd, char *str);
/// @brief create command struct
/// @param parser 
void lexical_analysis(t_parser *parser, t_shell *shell)
{   
	int i=0;
	t_lexel *tmp_lexel;
	t_cmd   *tmp_cmd;
	int     command_start;
	t_list  *tmp_node;


	tmp_node = parser->lexel_list;
	command_start = 0;
	tmp_cmd = NULL;
	if (tmp_node == NULL)
		return ;
	//@debug lexel list 
	while (tmp_node)
	{
		tmp_lexel = (t_lexel *)tmp_node->content;
		// No command in list
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
			{
				add_argument(tmp_cmd, tmp_lexel->str);
			}
		}

		if (tmp_lexel->type == D_REDIR_IN)
		{
			// oh found < 
			// @Start here

			tmp_node = redir_in(tmp_node, &tmp_cmd);
		}
		if (tmp_lexel->type == D_REDIR_OUT)
		{
			// oh found > 

			tmp_node = redir_out(tmp_node, &tmp_cmd);
		}

		// if (tmp_lexel->type == D_PIPE)
		// {
		//     // check create pipeline command keep result init
		//     // current command if fd out not change
		//     // pipe [cur_fdout | buff_cmd | new_cmd fd_in set to pipe] 
		// }

		if (tmp_node)
			tmp_node = tmp_node->next;
	}

	// test excute
	ft_lstadd_back(&shell->cmd_list, ft_lstnew(tmp_cmd));
	// debug_print_cmd(lst_getcmd(shell->cmd_list));
	execute(shell);
	ft_lstclear(&shell->cmd_list, free);
	// cmd_clear(tmp_cmd);
}

void    add_command_to_null_cmd(t_cmd *cmd, char *str)
{
	cmd->argval[0] = ft_strdup(str);
	cmd->cmd = ft_strdup(str);
	cmd->argcount++;
}

t_list  *redir_in(t_list *start, t_cmd **cur_cmd)
{
	t_list  *end;
	t_lexel *lex;
	t_cmd   *tmp_cmd;
	int     tmp_type;
	int     arrow_count;

	arrow_count = 0;
	if (!cur_cmd || !start)
		return (start);
	tmp_type = ((t_lexel *)start->content)->type;
	while (start)
	{
		lex = ((t_lexel *)start->content);
		if (lex->type  == tmp_type)
			arrow_count++;
		else if (lex->type == D_WORD)
		{
			open_for_read(arrow_count, lex->str, cur_cmd);
			break;
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

/// @brief To Handle heredoc and redirect in open file readmode and give it to cmd->fdstdin
/// @param arrow_count 
/// @param str 
/// @param curcmd 
void	open_for_read(int arrow_count, char *str,t_cmd **curcmd)
{
	int		file_to_open;
	char	*buffer;

	if (!curcmd)
		return ;
	if (!*curcmd)
		*curcmd = create_cmd(NULL);
	if ((*curcmd)->fd_stdin != STDIN_FILENO)
		close ((*curcmd)->fd_stdin);
	if (arrow_count == 1)
	{
		file_to_open = open(str, O_RDONLY, 0777);
	}
	else if (arrow_count == 2)
	{
		dprintf(2, RED"DOING HEREDOC"RESET);

		/// @brief just wait for heredoc
		file_to_open = 0;
	}
	(*curcmd)->fd_stdin = file_to_open;
}

/// @brief To handle redirect out in both mode
/// @param start content == lexer list
/// @param cur_cmd -> t_cmd
/// @return adress of node that be word or error if not found word
t_list  *redir_out(t_list *start, t_cmd **cur_cmd)
{
	t_list  *end;
	t_lexel *lex;
	t_cmd   *tmp_cmd;
	int     arrow_count;
	int     tmp_type;

	arrow_count = 0;
	if (!cur_cmd || !start)
		return (NULL);
	tmp_type = ((t_lexel *)start->content)->type;
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
				ft_putstr_fd(RED"ERROR\n"RESET, 2);
			break;
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

void    open_for_write(int arrow_count, char *str, t_cmd **curcmd)
{
	int     file_to_open;

	if (!curcmd)
		return ;
	if (*curcmd == NULL)
	{
		*curcmd = create_cmd(NULL);
	}
	if ((*curcmd)->fd_stdout != STDOUT_FILENO)
		close((*curcmd)->fd_stdout);
	if (arrow_count == 1)
		file_to_open = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (arrow_count == 2)
		file_to_open = open(str, O_WRONLY | O_CREAT | O_APPEND, 0777);
	(*curcmd)->fd_stdout = file_to_open;
}


void    cmd_clear(t_cmd *cmd)
{
	int i;

	i = 0;
	if (!cmd)
		return ;
	free(cmd->cmd);
	while (i < cmd->argcount)
	{
		free(cmd->argval[i]);
		i++;
	}
	free(cmd->argval);
	free(cmd);
}

t_cmd *lst_getcmd(t_list *lst)
{
	t_cmd *cmd;

	if (!lst)
		return (NULL);
	cmd = (t_cmd *)lst->content;
	return (cmd);
}

/// @brief add_argument to argument list however just alloc for 10 pointer char if execeed it will be realloced
/// @param cmd 
/// @param str 
void    add_argument(t_cmd *cmd, char *str)
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

t_cmd   *create_cmd(char *str)
{
	t_cmd   *new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->argval = ft_calloc(sizeof(char *), 10);
	if (str != NULL)
	{
		new_cmd->cmd = ft_strdup(str);
		new_cmd->argval[0] =ft_strdup(str);
		new_cmd->argcount = 1;
	}
	else
	{
		new_cmd->cmd = NULL;
		new_cmd->argval[0] = NULL;
		 new_cmd->argcount = 0;
	}
	new_cmd->max_arg = 9;
	new_cmd->fd_stdin = 0;
	new_cmd->fd_stdout = 1;
	return (new_cmd);
}

char    **ft_str2drelloc_free(char **str, int size)
{
	char    **new_str;
	int     i;

	i = 0;
	new_str = ft_calloc(sizeof(char *), size);
	while (i < (size - 10))
	{
		new_str[i] = ft_strdup(str[i]);
		i++;
	}
	// ft_str2diter(str, free);
	// free(str);
	return (new_str);
}