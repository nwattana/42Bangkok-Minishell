/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:31:27 by lkaewsae          #+#    #+#             */
/*   Updated: 2023/02/20 17:36:28 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_BUILTIN_H
# define MY_BUILTIN_H

# include "my_struct.h"
# include "here_doc.h"
# include "my_color.h"
# include "my_const.h"
# include "here_doc.h"
# include "minishell.h"

// builtin
int		ft_exit(t_cmd *exit, t_shell *shell);
int		ft_echo(t_cmd *cmd);
void	ft_env(char **env, t_shell *shell);
int		ft_pwd(t_shell *shell);
int		ft_export(t_cmd *cmd, t_shell *shell);
int		ft_unset(t_cmd *cmd, t_shell *shell);
int		ft_str2dlen(char **str);
int		ft_cd(t_cmd *cmd, t_shell *shell);
int		put_sort_env(t_shell *shell);

#endif
