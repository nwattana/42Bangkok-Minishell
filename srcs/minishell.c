/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 20:01:52 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/11 15:16:41 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
# include "debug.h"
int main(int argc, char **argv, char **env)
{
	char		*rl_line;
	t_shell		shell;

	if (argc == 0)
		(void)argv;
	init_shell(&shell, env);
	while (1)
	{
		rl_line = readline(PROMPT);
		if (ft_strncmp(rl_line, "exit", 4) == 0)
			break;
		process_line(rl_line);
//		add_history(line);
		printf(RED"line: %s\n"RESET, rl_line);
		free(rl_line);
	}
	// @skip no need to handle here it will update in future
	if (rl_line)
		free(rl_line);
	return (0);
}

void parser_init(t_parser *parser)
{
	parser->qoute_state = 0;
	parser->lexel_list = NULL;
	parser->tmp_lexel = NULL;
	parser->cur_word = NULL;
}

void process_line(char *line)
{
	t_parser	parser;
	int			i;
	int			tmp;
	char 		tmp_line;
	i = 0;
	tmp = 0;
	parser_init(&parser);
	while (line[i])
	{
		tmp = qoute_state_check(line[i], &parser);
		if (parser.qoute_state == 0 && ft_isdirection(&line[i]))
		{
			if (ft_lstsize(parser.cur_word) != 0)
			{
				add_lexel(&parser, D_WORD);
			}
			tmp_line = line[i];
			add_char(&parser, line[i]);
			add_lexel(&parser, line[i]);

			// @debug print word 1

		}
		else if (parser.qoute_state == '\"' && line[i] == '$')
		{
			// stop $ with alphabet or number
			// expand $env and join to current word
			i += get_dollar(&parser, &line[i]);
		}
		else if (parser.qoute_state == 0 && line[i] == ' ')
		{
			// init new word
			i += skip_space(&line[i]);

			/// @brief adding current group of word to lexer element list
			/// @param line 
			if (ft_lstsize(parser.cur_word) != 0)
			{
				// return error statement
				add_lexel(&parser, D_WORD);
			}
		}
		else if (!tmp)
		{
			if (line[i] == '$')
			{
				i += get_dollar(&parser, &line[i]);
			}
			else
				add_char(&parser, line[i]);
		}
		i++;
	}
	add_lexel(&parser, D_WORD);
//	lexical_analysis(&parser);
	// @debugzone
	debug_lstnext_show(parser.lexel_list);
	dump_lexel_list(parser.lexel_list);
	if (parser.qoute_state != 0)
		printf(RED"Error: qoute not closed\n"RESET);

	//@brif Note to delete parser element
	//destroy_parser(&parser);
}



/// @brief Check qoute state and change it
/// return new qoute state
int qoute_state_check(char a, t_parser *parser)
{
	if (parser->qoute_state == 0 && (a == '\'' || a == '\"'))
	{
		parser->qoute_state = a;
		return (1);
	}
	else if (parser->qoute_state == a)
	{
		parser->qoute_state = 0;
		return (1);
	}
	return (0);
}

void	destroy_parser(t_parser *parser)
{
	if (parser == NULL)
		return ;
	ft_lstclear(&parser->lexel_list, (void*)&lexel_del);
	ft_lstclear(&parser->cur_word, (void*)&free);
}


void lexel_del(t_lexel *lexel)
{
	if (lexel == NULL)
		return ;
	free(((t_lexel *)lexel)->str);
	free(lexel);
}

int	add_lexel(t_parser *parser, int type)
{
	char *word;

	if (parser == NULL)
		return (1);
	word = ft_lst_groupword(&parser->cur_word);
	if (word == NULL)
		return (1);
	parser->tmp_lexel = lexel_new(word, type);
	if (parser->tmp_lexel == NULL)
		return (1);
	parser->tmp_lst = ft_lstnew(parser->tmp_lexel);
	if (parser->tmp_lst == NULL)
		return (1);
	ft_lstadd_back(&parser->lexel_list, parser->tmp_lst);
	return (0);
}

int skip_space(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (i > 0)
		return (i - 1);
	return (i);
}

/// @brief 
/// @return 
int	ft_isdirection(char *c)
{
	if (c == NULL)
		return (0);
	if (*c == '>' || *c == '<' || *c == '|')
		return (1);
	return (0);
}

/// @brief Collection char and add to current word list
/// @return error code
int		add_char(t_parser *parser, char c)
{
	t_list *new;

	if (!parser)
		return (1);
	new = ft_lst_newchar(c);
	if (new == NULL)
		return (1);
	ft_lst_addword(&(parser->cur_word), new);
	return(0);
}

/// @brief create new list node with 
/// char content 2 bytes dont forget to free
t_list *ft_lst_newchar(char c)
{
	t_list *new;
	char *str;

	str = (char *)malloc(sizeof(char) * 2);
	if (str == NULL)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = str;
	new->next = NULL;
	return (new);
}

/// @brief add new node to the end of list with static last pointer
t_list *ft_lst_addword(t_list **lst, t_list *word)
{
	t_list *new;
	static t_list *last;
	
	if (lst == NULL || word == NULL)
		return (NULL);
	if (*lst == NULL)
	{
		*lst = word;
		last = word;
	}
	else
	{
		last->next = word;
		last = word;
	}
	return (last);
}

/// @brief collect all char in list and return string 
/// already free list and content
/// dont forget to free returned string
char *ft_lst_groupword(t_list **lst)
{
	t_list *tmp;
	char *str;
	int i;

	if (lst == NULL || *lst == NULL)
		return (NULL);
	i = ft_lstsize(*lst);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (*lst)
	{
		str[i] = ((char *)(*lst)->content)[0];
		i++;
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp->content);
		tmp->content = NULL;
		free(tmp);
	}
	tmp = NULL;
	str[i] = '\0';
	return (str);
}

int		get_dollar(t_parser *parser, char *line)
{
	int     i;
	int     size;
	char	*tmp;
	char	*val;

	i = 0;
	while (line [i] && line[i + 1] && ft_isalnum(line[i + 1]))
		i++;
	if (i == 0)
		return (check_reserverd(parser, line));
	if (i > 0)
	{
		tmp = ft_substr(line, 1, i);
		val = getenv(tmp);
	}
	size = 0;
	while (val != NULL && val[size])
	{
		add_char(parser, val[size]);
		size++;
	}
	free(tmp);
	return (i);
}

int		check_reserverd(t_parser *parser, char *line)
{
	char *tmp;
	int i;

	i = 0;
	if (line[0] == '$')
	{
		tmp =ft_itoa(getpid());
		while (tmp[i])
		{
			add_char(parser, tmp[i]);
			i++;
		}
		return (1);
	}
	//  && line[1] == '?' exit status
	return (0);
}

t_lexel *lexel_new(char *str, int type)
{
	t_lexel *new;

	new = (t_lexel *)malloc(sizeof(t_lexel));
	if (new == NULL)
		return (NULL);
	new->str = str;
	new->type = type;
	return (new);
}
