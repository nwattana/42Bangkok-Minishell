/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:01:07 by lkaewsae          #+#    #+#             */
/*   Updated: 2023/02/19 14:16:18 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtin.h"

// maximum path length = 4096 byte
int		ft_pwd(t_shell *shell)
{
	// check is null or not
	char	*path;

	printf("%d\n",PATH_MAX);
	path = malloc(sizeof(char) * 4097);
	path = getcwd(path, 4097);
	ft_putendl_fd(path, 1);
	free(path);
	exit(0);
	return (0);
}