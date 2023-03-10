/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_const.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 01:16:27 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/21 15:44:32 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_CONST_H
# define MY_CONST_H

# define BUFF_SIZE 1

# define MAX_FD 1024
# define MAX_INT 2147483647
# define MIN_INT -2147483648
# define MAX_UINT 4294967295
# define PROMPT "minishell> "

# define D_EOW 0
# define D_WORD 1
# define D_REDIR_OUT 62
# define D_REDIR_IN 60
# define D_REDIR_APPEND 62
# define D_REDIR_HEREDOC 60
# define D_PIPE 124

# define LEX_PIPE_IN 10
# define LEX_PIPE_OUT 20

# define PIPE_READ_END 0
# define PIPE_WRITE_END 1

# define TO_BADUSER "Something wrong !! : "
#endif