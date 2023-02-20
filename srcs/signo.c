/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaewsae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:04:51 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/21 03:07:12 by lkaewsae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sig_handling(int sig, siginfo_t *siginfo, void *context)
{
	if (sig == SIGTERM)
	{
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
