/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <nwattana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:33:04 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/08 14:03:41 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H
# include "minishell.h"

void debug_lstnext_show(t_list *lst);
void debug_lexel_print(t_lexel *lexel);
void dump_lexel_list(t_list *head);
#endif