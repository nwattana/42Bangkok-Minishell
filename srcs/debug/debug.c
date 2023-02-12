/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:32:18 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/12 02:59:46 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/debug.h"

void	debug_lexel_print(t_lexel *lexel)
{
	if (lexel == NULL)
		return ;
	printf("lexel: %s, type: %d\n", lexel->str, lexel->type);
}

void dump_lexel_list(t_list *head)
{
	t_list *tmp;

	ft_lstiter(head, (void *)debug_lexel_print);
	tmp = head;
	while (tmp)
	{
		if (((t_lexel *)tmp->content)->type == 0)
			printf("\"%s\"-> ", ((t_lexel *)tmp->content)->str);
		else
			printf("%s -> ", ((t_lexel *)tmp->content)->str);
		tmp = tmp->next;
	}
	tmp = head;
	printf("\n");
	while (tmp)
	{
		printf("%d -> ", ((t_lexel *)tmp->content)->type);
		tmp = tmp->next;
	}
}

void	debug_lstnext_show(t_list *head)
{
	t_list *tmp;

	tmp = head;
	while (tmp)
	{
		printf("%p -> ", tmp);
		tmp = tmp->next;
	}
	printf("NULL\n");
}

void	dump_parser(t_parser *parser)
{
	ft_lstiter(parser->cmd_list, cmd_dump);
}

void	cmd_dump(void *content)
{
	t_cmd *tmp;

	tmp = (t_cmd *)content;
	printf("cmd = %s av = %d\n",tmp->cmd, tmp->argcount);
	ft_str2diter(tmp->argval, ft_debug_greenstr_nl);
	
}

void	debug_print_cmd(t_cmd *cmd)
{
	int i;

	i = 0;
	printf("cmd = %s \n argc = %d\n",cmd->cmd, cmd->argcount);
	while (i < cmd->argcount)
	{
		printf("arg[%d] = %s\n", i, cmd->argval[i]);
		i++;
	}
}

void    ft_debug_greenstr_nl(char *str)
{
    printf(GREEN"%s\n"RESET,str);
}