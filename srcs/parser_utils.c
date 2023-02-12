/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:59:58 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/12 15:18:25 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/// @brief Check quote state and change it
/// return new quote state
int quote_state_check(char a, t_parser *parser)
{
	if (parser->quote_state == 0 && (a == '\'' || a == '\"'))
	{
		parser->quote_state = a;
		return (1);
	}
	else if (parser->quote_state == a)
	{
		parser->quote_state = 0;
		return (1);
	}
	return (0);
}

// clean parser element
void	destroy_parser(t_parser *parser)
{
	if (parser == NULL)
		return ;
	ft_lstclear(&parser->lexel_list, (void*)&lexel_del);
	ft_lstclear(&parser->cur_word, (void*)&free);
}

// free lexer element
void lexel_del(t_lexel *lexel)
{
	if (lexel == NULL)
		return ;
	free(((t_lexel *)lexel)->str);
	free(lexel);
}

/// @brief collect or word in curword list then
/// create lexer element in TYPE from param
/// create linked list node -> add to parser->lexel_list
/// @param type WORD PIPR DIRECTION 
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

/// @brief pass amount of contiguose space
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

/// @brief why char* not only char
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
	// ไม่ได้ใช้ @wait for show exit status
	if (line[0] == '$')
	{
		tmp =ft_itoa(getpid());
		while (tmp[i])
		{
			add_char(parser, tmp[i]);
			i++;
		}
		free(tmp);
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

void parser_init(t_parser *parser)
{
	parser->quote_state = 0;
	parser->lexel_list = NULL;
	parser->tmp_lexel = NULL;
	parser->cur_word = NULL;
	parser->is_char_or_quote = 0;
}
