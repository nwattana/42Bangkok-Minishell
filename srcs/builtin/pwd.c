/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:01:07 by lkaewsae          #+#    #+#             */
/*   Updated: 2023/02/19 22:46:47 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtin.h"

// maximum path length = 4096 byte
// set OLDPWD
int		ft_pwd(t_shell *shell)
{
	// check is null or not
	char	*path;

	path = malloc(sizeof(char) * (PATH_MAX + 1));
	path = getcwd(path, PATH_MAX);
	ft_putendl_fd(path, 1);
	free(path);
	exit(0);
	return (0);
}