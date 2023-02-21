/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:04:51 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/21 12:32:35 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern	t_shell	*g_shell;

void	sig_handling(int sig)
{
	if (sig == SIGTERM)
	{
		rl_replace_line(PROMPT" exit", 0);
		rl_redisplay();
		univesal_clear(g_shell);
		exit(SIGTERM);
	}
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_signal(t_shell *shell)
{	
	rl_catch_signals = 0;
	
	sigemptyset(&(shell->signo.sa_mask));
	sigemptyset(&(shell->signquit.sa_mask));
	sigaddset(&(shell->signquit.sa_mask), SIGQUIT);

	sigaddset(&(shell->signo.sa_mask), SIGINT);
	sigaddset(&(shell->signo.sa_mask), SIGTERM);
	shell->signquit.sa_handler = SIG_IGN;
	shell->signo.sa_handler = sig_handling;
	
	sigaction(SIGQUIT, &(shell->signquit), NULL);
	sigaction(SIGINT, &(shell->signo), NULL);
	sigaction(SIGTERM, &(shell->signo), NULL);
}

// void	set_signal(t_shell *shell)
// {
// 	rl_catch_signals = 0;
// 	sigemptyset(&(shell->signquit.sa_mask));
// 	sigaddset(&(shell->signquit.sa_mask), SIGQUIT);
// 	shell->signquit.sa_handler = SIG_IGN;
// 	sigaction(SIGQUIT, &(shell->signquit), NULL);

// 	signal(SIGTERM, sig_handling);
// 	signal(SIGINT, sig_handling);
// }
