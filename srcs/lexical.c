/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:12:14 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/12 17:24:39 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"
# include "../inc/debug.h"
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
                tmp_cmd = create_cmd(tmp_lexel->str);
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
        // if (tmp_lexel->type == D_REDIR_IN)
        // {
        //     // check 
        // }
        // if (tmp_lexel->type == D_REDIR_OUT)
        // {
        //     // oh found > 
        //     tmp_node = redir_out(tmp_node, &tmp_cmd);
        // }
        // if (tmp_lexel->type == D_PIPE)
        // {
        //     // check create pipeline command keep result init
        //     // current command if fd out not change
        //      // pipe [cur_fdout | buff_cmd | new_cmd fd_in set to pipe] 
        // }
        tmp_node = tmp_node->next;
    }
    // test excute
    
    ft_lstadd_back(&shell->cmd_list, ft_lstnew(tmp_cmd));
    ft_debug_greenstr_nl("TMP CMD\n");
    debug_print_cmd(lst_getcmd(shell->cmd_list));
    execute(shell);
    ft_lstclear(&shell->cmd_list, free);
    // cmd_clear(tmp_cmd);
}

t_list  *redir_out(t_list *start, t_cmd *cmd)
{
    t_list  *end;
    t_list  *tmp_lst_travers;
    t_cmd   *tmp_cmd;

    if (!cmd | !start)
        return (NULL);
    while (start)
    {
        start = start->next;
    }
   return (end); 
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

    if (!str)
        return (NULL);
    new_cmd = malloc(sizeof(t_cmd));
    if (!new_cmd)
        return (NULL);
    new_cmd->cmd = ft_strdup(str);
    new_cmd->argval = ft_calloc(sizeof(char *), 10);
    new_cmd->argval[0] =ft_strdup(str);
    new_cmd->argcount = 1;
    new_cmd->max_arg = 9;
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