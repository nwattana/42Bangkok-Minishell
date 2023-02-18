/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:32:18 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/17 22:38:42 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/debug.h"
#include "../inc/minishell.h"

void	debug_lexel_print(t_lexel *lexel)
{
	if (lexel == NULL)
		return ;
	dprintf(2,"lexel: %s, type: %d\n", lexel->str, lexel->type);
}

void dump_lexel_list(t_list *head)
{
	t_list *tmp;

	ft_lstiter(head, (void *)debug_lexel_print);
	tmp = head;
	while (tmp)
	{
		if (((t_lexel *)tmp->content)->type == 0)
			dprintf(2,"\"%s\"-> ", ((t_lexel *)tmp->content)->str);
		else
			dprintf(2,"%s -> ", ((t_lexel *)tmp->content)->str);
		tmp = tmp->next;
	}
	tmp = head;
	dprintf(2,"\n");
	while (tmp)
	{
		dprintf(2,"%d -> ", ((t_lexel *)tmp->content)->type);
		tmp = tmp->next;
	}
}

void	debug_lstnext_show(t_list *head)
{
	t_list *tmp;

	tmp = head;
	while (tmp)
	{
		dprintf(2,"%p -> ", tmp);
		tmp = tmp->next;
	}
	dprintf(2,"NULL\n");
}

void	dump_parser(t_parser *parser)
{
	ft_lstiter(parser->cmd_list, cmd_dump);
}

void	cmd_dump(void *content)
{
	t_cmd *tmp;

	if (!content)
		return (void)dprintf(2, \
		RESET"Command IS NULL "
		RED"A"
		GREEN"i "
		BLUE"S"
		GREEN"U"
		RED"S"
		RESET"pect some where wrong\n");
	tmp = (t_cmd *)content;
	dprintf(2,GREEN"-----------------------\n"RESET);
	dprintf(2,"cmd = %s av = %d\n",tmp->cmd, tmp->argcount);
	ft_str2diter(tmp->argval, ft_debug_greenstr_nl);
	dprintf(2,"STDOUT = %d\n", tmp->fd_stdout);
	dprintf(2,"STDIN = %d\n", tmp->fd_stdin);
	dprintf(2,"PIPEline state = %d\n", tmp->pipeline_state);
	if (tmp->here_doc_status)
		dprintf(2,"Here doc = %s\n", tmp->heredoc_filename);
	
	dprintf(2,RED"-----------------------\n"RESET);
	
}

void	debug_print_cmd(t_cmd *cmd)
{
	int i;

	i = 0;
	dprintf(2,"cmd = %s \n argc = %d\n",cmd->cmd, cmd->argcount);
	while (i < cmd->argcount)
	{
		dprintf(2,"arg[%d] = %s\n", i, cmd->argval[i]);
		i++;
	}
	dprintf(2,"STDOUT = %d\n", cmd->fd_stdout);
	dprintf(2,"STDIN = %d\n", cmd->fd_stdin);
}

void    ft_debug_greenstr_nl(char *str)
{
    dprintf(2,GREEN"%s\n"RESET,str);
}