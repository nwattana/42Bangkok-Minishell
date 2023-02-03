/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:46:42 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/03 21:20:47 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "my_color.h"
# include "my_const.h"


typedef struct s_cmd
{
    int     stdin;
    int     stdout;
    int     stderr;
	char	*cstdin;
	char	*cstdout;
	char	*cstderr;
    char	*cmd;
    char	**args;
}				t_cmd;

typedef struct s_lexerelement
{
    int     type;
    char    *str;
}				t_lexel;;

typedef struct s_parser
{
	int		qoute_state;
    t_list  *word_line;
	t_list	*cur_word;

}				t_parser;

int qoute_state_check(char a, t_parser *parser);
void process_line(char *line);
int	ft_isdirection(char *c);
t_list 		*ft_lst_newchar(char c);
t_list 		*ft_lst_addword(t_list **lst, t_list *word);
int			add_char(t_parser *parser, char c);
char *ft_lst_groupword(t_list **lst);
int		get_dollar(t_parser *parser, char *line);
t_lexel	*lexel_new(char *str, int type);

void lexel_debug(t_lexel *lexel);


#endif