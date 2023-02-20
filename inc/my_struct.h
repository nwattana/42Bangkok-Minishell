/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:30:15 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/21 01:25:10 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_STRUCT_H
# define MY_STRUCT_H

# include "../libft/libft.h"

typedef struct s_cmd
{
	char	*cmd;
	char	**argval;
	int		argcount;
	int		fd_stdin;
	int		fd_stdout;
	char	*heredoc_filename;
	int		here_doc_status;
	int		*pipein;
	int		pipeout[2];
	int		pipeline_state;
	int		cmd_status;
	int		cmd_exit_status;
	int		cmd_pre_exit_status;
	int		max_arg;
}				t_cmd;

typedef struct s_lexerelement
{
	char	*str;
	int		type;
}				t_lexel;

typedef struct s_parser
{
	int		quote_state;
	int		is_char_or_quote;
	t_lexel	*tmp_lexel;
	t_list	*tmp_lst;
	t_list	*lexel_list;
	t_list	*cur_word;
	t_list	*cmd_list;
}				t_parser;

typedef struct s_shell
{
	char				*line;
	char				**env;
	char				**path;
	char				*pwd;
	int					last_status;
	int					sh_stdin;
	int					sh_stdout;
	t_list				*cmd_list;
	struct sigaction	signo;
	struct sigaction	signquit;
}				t_shell;

#endif