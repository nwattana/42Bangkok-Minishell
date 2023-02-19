/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:00:58 by lkaewsae          #+#    #+#             */
/*   Updated: 2023/02/20 02:26:20 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtin.h"
//2 ways exit

// following by exit status number or something
// no argument exit 0
// argument number -> exit = num % 256
static int	check_is_digit(char *str);

int		ft_exit(t_cmd *cmd, t_shell *shell)
{
	int		status;

	if (cmd->fd_stdin != 0 || cmd->fd_stdout != 1)
		return (1);
	if (cmd->argcount > 1 && cmd->argcount < 3)
	{
		ft_putstr_fd("exit\n", 2);
		if (check_is_digit(cmd->argval[1]) == 1)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd->argval[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
		exit(ft_atoi(cmd->argval[1]) % 256);
	}
	else if (cmd->argcount >= 3)
	{
		ft_putstr_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	exit(0);
}

static int		check_is_digit(char *str)
{
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (1);
		str++;
	}
	return (0);
}