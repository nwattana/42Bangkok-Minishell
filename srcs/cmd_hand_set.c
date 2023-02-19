/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_hand_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:36:47 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/19 23:41:22 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_cmd	*cmd_hand_gen(char *cmdin, char *argv)
{
	t_cmd *cmd;

	cmd = create_cmd(cmdin);
	add_argument(cmd, argv);
	return (cmd);
}