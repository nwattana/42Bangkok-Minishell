/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:46:42 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/20 18:05:52 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <limits.h>
# include "../libft/libft.h"
# include "my_color.h"
# include "my_const.h"
# include "here_doc.h"
# include "my_builtin.h"
# include "my_struct.h"

// parser smol expand
int		add_char(t_parser *parser, char c);
int		add_lexel(t_parser *parser, int type);
t_list	*ft_lst_newchar(char c);
t_list	*ft_lst_addword(t_list **lst, t_list *word);
char	*ft_lst_groupword(t_list **lst);
int		ft_isdirection(char *c);
int		get_dollar(t_parser *parser, char *line, t_shell *shell);
t_lexel	*lexel_new(char *str, int type);
void	process_line(char *line, t_shell *shell);
void	parser_init(t_parser *parser);
int		quote_state_check(char a, t_parser *parser);
int		skip_space(char *line);

// init shell
void	init_shell(t_shell *shell, char **env);
void	ft_putstr_env(char *str);
void	ft_str2diter(char **str, void (*f)(void *));
void	clone_env(t_shell *shell, char **env);

// lexical analysis
void	lexical_analysis(t_parser *parser, t_shell *shell);
t_cmd	*create_cmd(char *str);
void	add_argument(t_cmd *cmd, char *str);
char	**ft_str2drelloc_free(char **str, int size);
t_cmd	*lst_getcmd(t_list *lst);
t_cmd	*cmd_hand_gen(char *cmdin, char *argv);

// clear
void	cmd_clear(void *vtf_cmd);
void	clean_lexel(void *lexel);
void	clean_parser(void *parser);
void	destroy_parser(t_parser *parser);
void	lexel_del(t_lexel *lexel);
void	clear_hd(void *vtf_cmd);
void	free_null(void	*val);

// execute
void	close_pipe(t_cmd *cmd, int *std);
char	*check_access(t_cmd *cmd, t_shell *shell);
void	ex_cute(t_cmd *cmd, t_shell *shell);
int		direction_pipeline(t_list *cmd_list, t_shell *shell);
void	get_status(t_shell *sh);

// redirect
t_list	*redir_out(t_list *start, t_cmd **cur_cmd);
t_list	*redir_in(t_list *start, t_cmd **cur_cmd);
void	open_for_write(int arrow_count, char *str, t_cmd **curcmd);
void	open_for_read(int arrow_count, char *str, t_cmd **curcmd);
void	add_command_to_null_cmd(t_cmd *cmd, char *str);
int		*to_pipe(t_cmd *cmd);
int		iscmd_inbuilt_in(t_cmd *cmd, t_shell *shell, int pid);
char	**ft_str2d_addmem(char **str, char *new_str);

// universal clear 
void	univesal_clear(t_shell *shell);

// env utils
int		check_env_valid_key(char *key, t_shell *sh);
int		create_tmp_key(char **buf, char *key);
char	*get_env_from_key(char *key, t_shell *shell);
void	path_update(t_shell *shell);

// signal
void	set_signal(t_shell *shell);
void	sig_handling(int sig);

#endif
