/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:12:14 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/18 11:21:32 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"
# include "../inc/debug.h"


/// @brief create command struct
/// @param parser 
void lexical_analysis(t_parser *parser, t_shell *shell)
{   
	int i = 0;
	t_lexel *tmp_lexel;
	t_cmd   *tmp_cmd;
	int     command_start;
	t_list  *tmp_node;
	int		pipe_is_open;
	int		*from_pipe;

	// initial
	pipe_is_open = 0;
	tmp_node = parser->lexel_list;
	command_start = 0;
	tmp_cmd = NULL;

	if (tmp_node == NULL)
		return ;
	//@debug lexel list 
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
			{
				add_argument(tmp_cmd, tmp_lexel->str);
			}
		}

		if (tmp_lexel->type == D_REDIR_IN)
		{
			tmp_node = redir_in(tmp_node, &tmp_cmd);
		}
		if (tmp_lexel->type == D_REDIR_OUT)
		{
			tmp_node = redir_out(tmp_node, &tmp_cmd);
		}
		if (tmp_lexel->type == D_PIPE)
		{
			// combination of pipe and redir
			// echo cc >> hello | cat -e -> cat do nothing
			// create piping in to next cmd
			from_pipe = to_pipe(tmp_cmd);
			if (tmp_cmd != NULL)
			{
				ft_lstadd_back(&shell->cmd_list, ft_lstnew(tmp_cmd));
			}
			else
			{
				ft_putstr_fd(RED"Error: PIPE From Nothing is NULL\n"RESET, 2);
			}
			tmp_cmd = create_cmd(NULL);
			tmp_cmd->fd_stdin = from_pipe[0];
			tmp_cmd->pipein = from_pipe;
			tmp_cmd->pipeline_state += 2;
			command_start = 0;
			// make write end
			// finish write end
			// create read end -> null str name
			// set cmd-start to NULL
		}
		if (tmp_node)
			tmp_node = tmp_node->next;
	}
	// optimise with queue style
	ft_lstadd_back(&shell->cmd_list, ft_lstnew(tmp_cmd));
	// @debug printf cmd list
	ft_lstiter(shell->cmd_list, cmd_dump);

//	execute(shell);
	ft_lstclear(&shell->cmd_list, cmd_clear);
}


/// @brief  add current command direction out
/// @param cmd 
int	*to_pipe(t_cmd *cmd)
{
	static int pindex;
	
	pipe(cmd->pipeout);
	// already have fd out
	// but should have pipe to next command
	if (cmd->fd_stdout != 1)
	{
		close(cmd->pipeout[0]);
	}
	else
	{
		cmd->fd_stdout = cmd->pipeout[1];
		cmd->pipeline_state += 1;
	}
	// @debug 
	dprintf(2,"PIPE {"RED"%d"WHITE"} [%d][%d] \n",pindex, cmd->pipeout[0], cmd->pipeout[1]);
	pindex++;
	return (cmd->pipeout);
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

// clear here doc file
// and set here doc status to 0
void	clear_hd(void *vtf_cmd)
{
	t_cmd *cmd;

	if (!vtf_cmd)
		return ;
	cmd = (t_cmd *)vtf_cmd;
	if (cmd->here_doc_status)
	{
		unlink(cmd->heredoc_filename);
		free(cmd->heredoc_filename);
		cmd->heredoc_filename = NULL;
	}
	cmd->here_doc_status = 0;
}