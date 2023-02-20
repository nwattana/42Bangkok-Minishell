/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:01:07 by lkaewsae          #+#    #+#             */
/*   Updated: 2023/02/20 17:34:43 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/my_builtin.h"

// maximum path length = 4096 byte NOP == PATH_MAX
int	ft_pwd(t_shell *shell)
{
	char	*path;

	path = malloc(sizeof(char) * (PATH_MAX + 1));
	path = getcwd(path, PATH_MAX);
	ft_putendl_fd(path, 1);
	free(path);
	exit(0);
	return (0);
}
