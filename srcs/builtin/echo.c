/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:58:22 by lkaewsae          #+#    #+#             */
/*   Updated: 2023/02/20 02:20:59 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtin.h"
#include "../../inc/debug.h"
int	ft_echo(t_cmd *cmd)
{
	int		nl;
	int		i;
	char	**argv;

	i = 1;
	nl = 0;
	argv=cmd->argval;
	while (cmd->argcount != 1 &&ft_strcmp(argv[i], "-n") == 0)
	{
		nl = 1;
		i++;
		cmd->argcount--;
	}
	while (cmd->argcount != 1 && argv[i])
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
