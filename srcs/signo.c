/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaewsae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:04:51 by nwattana          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/21 03:07:12 by lkaewsae         ###   ########.fr       */
=======
/*   Updated: 2023/02/21 01:31:33 by nwattana         ###   ########.fr       */
>>>>>>> 165e408bb7d52839f2400a2186bf002b11fa8ad5
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern	t_shell	*G_SHELL;

void	sig_handling(int sig)
{
	if (sig == SIGTERM)
	{
<<<<<<< HEAD
		printf("\n SIGTERM %d\n", SIGTERM);
		exit(SIGTERM);
	}
	if (sig == SIGQUIT)
	{
		printf("\n");
	}
	if (sig == SIGINT)
	{
		printf("\n SIGINT %d\n", SIGINT);
		return ;
=======
		rl_replace_line(PROMPT" exit", 0);
		rl_redisplay();
		univesal_clear(G_SHELL);
		exit(SIGTERM);
	}
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
>>>>>>> 165e408bb7d52839f2400a2186bf002b11fa8ad5
	}
}

void	set_signal(t_shell *shell)
{	
	rl_catch_signals = 0;
	
	sigemptyset(&(shell->signo.sa_mask));
<<<<<<< HEAD
	sigaddset(&(shell->signo.sa_mask), SIGTERM);
	sigaddset(&(shell->signo.sa_mask), SIGQUIT);
	sigaddset(&(shell->signo.sa_mask), SIGINT);
	shell->signo.sa_sigaction = sig_handling;
	shell->signo.sa_flags = SA_RESTART;
	sigaction(SIGTERM, &(shell->signo), NULL);
	sigaction(SIGQUIT, &(shell->signo), NULL);
	sigaction(SIGINT, &(shell->signo), NULL);
=======
	sigemptyset(&(shell->signquit.sa_mask));
	sigaddset(&(shell->signquit.sa_mask), SIGQUIT);

	sigaddset(&(shell->signo.sa_mask), SIGINT);
	sigaddset(&(shell->signo.sa_mask), SIGTERM);
	shell->signquit.sa_handler = SIG_IGN;
	shell->signo.sa_handler = sig_handling;
	
	sigaction(SIGQUIT, &(shell->signquit), NULL);
	sigaction(SIGINT, &(shell->signo), NULL);
	sigaction(SIGTERM, &(shell->signo), NULL);
>>>>>>> 165e408bb7d52839f2400a2186bf002b11fa8ad5
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
