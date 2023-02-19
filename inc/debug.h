/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:33:04 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/20 02:00:28 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H
# include "minishell.h"

void 	debug_lstnext_show(t_list *lst);
void 	debug_lexel_print(t_lexel *lexel);
void 	dump_lexel_list(t_list *head);
void	cmd_dump(void *content);
void	dump_parser(t_parser *parser);
void	debug_print_cmd(t_cmd *cmd);
void    ft_debug_greenstr_nl(void *str);

#endif