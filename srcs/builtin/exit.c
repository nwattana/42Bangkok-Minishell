/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaewsae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:00:58 by lkaewsae          #+#    #+#             */
/*   Updated: 2023/02/21 01:06:55 by lkaewsae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/my_builtin.h"

//2 ways exit
// following by exit status number or something
// no argument exit 0
// argument number -> exit = num % 256
static int	check_is_digit(char *str);
static void	univesal_clear_extend(t_shell *shell, int status);

void	univesal_clear_extend(t_shell *shell, int status)
{
	univesal_clear(shell);
	exit(status);
}

int	ft_exit(t_cmd *cmd, t_shell *shell)
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
			univesal_clear_extend(shell, 255);
		}
		univesal_clear_extend(shell, ft_atoi(cmd->argval[1]) % 256);
	}
	else if (cmd->argcount >= 3)
	{
		ft_putstr_fd("minishell: exit: too many arguments", 2);
		univesal_clear(shell);
		return (1);
	}
	univesal_clear_extend(shell, 0);
	return (status);
}

static int	check_is_digit(char *str)
{
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (1);
		str++;
	}
	return (0);
}

// clear memory for exit
void	univesal_clear(t_shell *shell)
{
	if (shell->line)
		free_null(shell->line);
	if (shell->env)
	{
		ft_str2diter(shell->env, free_null);
		free_null(shell->env);
	}
	if (shell->path)
	{
		ft_str2diter(shell->path, free_null);
		free_null(shell->path);
	}
	if (shell->pwd)
		free(shell->pwd);
	if (shell->cmd_list)
		ft_lstiter(shell->cmd_list, cmd_clear);
	clear_history();
}
