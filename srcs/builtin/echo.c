/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:58:22 by lkaewsae          #+#    #+#             */
/*   Updated: 2023/02/19 14:20:06 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtin.h"

int	ft_echo(char **argv)
{
	int		nl;
	int		i;

	i = 1;
	nl = 0;
	dprintf(2,GREEN"Built in\n"RESET);
	while (ft_strcmp(argv[i], "-n") == 0)
	{
		nl = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		i++;
		if (argv[i])
			ft_putstr_fd(" ", 1);
	}
	if (!nl)
		ft_putstr_fd("\n", 1);
	exit(0);
}
