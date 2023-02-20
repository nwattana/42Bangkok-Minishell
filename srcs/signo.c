/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:04:51 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/20 18:33:22 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sig_handling(int sig, siginfo_t *siginfo, void *context)
{
	if (sig == SIGTERM)
	{
		// ctrl + d//
		printf("\n SIGTERM %d\n", SIGTERM);
		exit(SIGTERM);
	}
	if (sig == SIGQUIT)
	{
		// ctrl + \//
		printf("\n");
	}
	if (sig == SIGINT)
	{
		// ctrl + c//
		printf("\n SIGINT %d\n", SIGINT);
		return ;
	}
}

void	set_signal(t_shell *shell)
{
	sigemptyset(&(shell->signo.sa_mask));
	sigaddset(&(shell->signo.sa_mask), SIGTERM);
	sigaddset(&(shell->signo.sa_mask), SIGQUIT);
	sigaddset(&(shell->signo.sa_mask), SIGINT);
	shell->signo.sa_sigaction = sig_handling;
	shell->signo.sa_flags = SA_RESTART;
	sigaction(SIGTERM, &(shell->signo), NULL);
	sigaction(SIGQUIT, &(shell->signo), NULL);
	sigaction(SIGINT, &(shell->signo), NULL);

	
}
