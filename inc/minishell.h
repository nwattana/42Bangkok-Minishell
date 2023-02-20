/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:46:42 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/20 13:35:05 by nwattana         ###   ########.fr       */
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
# include "builtin.h"


// @attribut pipeline state =>
// keep state too how to close pipe and pipe open or not
typedef struct sigaction t_sig;
typedef struct s_cmd
{
	char	*cmd;
	char	**argval;
	int     argcount;

	int     fd_stdin;
	int     fd_stdout;

	char	*heredoc_filename;
	int		here_doc_status;

	// contain previous cmd pipeout
	int		*pipein;
	// contain current cmd stdout
	int     pipeout[2];
	
	int     pipeline_state;
	int		cmd_status;
	int		cmd_exit_status;
	int		cmd_pre_exit_status;
	int     max_arg;
}				t_cmd;


/// @brief group argument in lexical_analysis
typedef struct s_lexeranalysis
{
	int     iter;

}           t_lexa;

typedef struct s_lexerelement
{
	char    *str;
	int     type;
}				t_lexel;;

/// @attribute tmp_lexel; ->
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
	char    *line;
	char    **env;
	char    **path;
	char    *home;
	char    *pwd;
	char	*oldpwd;
	int		last_status;
	int     sh_stdin;
	int     sh_stdout;
	t_sig	signal_val;

	t_list  *cmd_list;
}				t_shell;

// parser smol expand
int		quote_state_check(char a, t_parser *parser);
void	process_line(char *line, t_shell *shell);
int		ft_isdirection(char *c);
void	parser_init(t_parser *parser);
t_list	*ft_lst_newchar(char c);
t_list 	*ft_lst_addword(t_list **lst, t_list *word);
int		add_char(t_parser *parser, char c);
char	*ft_lst_groupword(t_list **lst);
int		get_dollar(t_parser *parser, char *line, t_shell *shell);

t_lexel	*lexel_new(char *str, int type);
int 	skip_space(char *line);
int		add_lexel(t_parser *parser, int type);

// init shell
void	init_shell(t_shell *shell, char **env);
void	ft_putstr_env(char *str);
void	ft_str2diter(char **str, void (*f)(void *));
void	clone_env(t_shell *shell, char **env);

// lexical analysis
void    lexical_analysis(t_parser *parser, t_shell *shell);
t_cmd   *create_cmd(char *str);
void    add_argument(t_cmd *cmd, char *str);
char    **ft_str2drelloc_free(char **str, int size);
t_cmd   *lst_getcmd(t_list *lst);
t_cmd	*cmd_hand_gen(char *cmdin, char *argv);
// clear
void    cmd_clear(void *vtf_cmd);


void destroy_parser(t_parser *parser);
void lexel_del(t_lexel *lexel);

// execute
void	close_pipe(t_cmd *cmd, int *std);
char    *check_access(t_cmd *cmd, t_shell *shell);
void	ex_cute(t_cmd *cmd, t_shell *shell);
int		direction_pipeline(t_list *cmd_list, t_shell *shell);


// redirect
t_list  *redir_out(t_list *start, t_cmd **cur_cmd);
t_list  *redir_in(t_list *start, t_cmd **cur_cmd);
void    open_for_write(int arrow_count, char *str, t_cmd **curcmd);
void	open_for_read(int arrow_count, char *str,t_cmd **curcmd);
void    add_command_to_null_cmd(t_cmd *cmd, char *str);
int		*to_pipe(t_cmd *cmd);

int		iscmd_inbuilt_in(t_cmd *cmd, t_shell *shell, int pid);
char	**ft_str2d_addmem(char **str, char *new_str);

// clear
void	clear_hd(void *vtf_cmd);
void	free_null(void	**val);

// universal clear


// just utility


// env utils
int		check_env_valid_key(char *key, t_shell *sh);
int		create_tmp_key(char **buf, char *key);
char	*get_env_from_key(char *key, t_shell *shell);
void	path_update(t_shell *shell);

// builtin
void	ft_env(char **env, t_shell *shell);
int		ft_pwd(t_shell *shell);
int		ft_export(t_cmd *cmd, t_shell *shell);
int		ft_unset(t_cmd *cmd, t_shell *shell);
int		ft_str2dlen(char **str);
int		ft_cd(t_cmd *cmd, t_shell *shell);
int		ft_exit(t_cmd *exit, t_shell *shell);
int		ft_echo(t_cmd *cmd);

#endif
