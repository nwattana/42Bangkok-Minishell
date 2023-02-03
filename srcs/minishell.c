/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 20:01:52 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/03 15:06:56 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(void)
{
	char		*rl_line;
	//t_shell		shell;

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
	return (0);
}

void parser_init(t_parser *parser)
{
	parser->qoute_state = 0;
	parser->cur_word = NULL;
}

void process_line(char *line)
{
	t_parser	parser;
	int			i;
	char 		*word;
	int			tmp;

	i = 0;
	tmp = 0;
	parser_init(&parser);
	while (line[i])
	{
		tmp = qoute_state_check(line[i], &parser);
		if (parser.qoute_state == 0 && ft_isdirection(&line[i]))
		{
			// init new cmd
			// add current word to cmd
			word = ft_lst_groupword(&parser.cur_word);
			printf("word: %s\n", word);

		}
		else if (parser.qoute_state == '\"' && line[i] == '$')
		{
			// stop $ with alphabet or number
			// expand $env and join to current word
			i += get_dollar(&parser, &line[i]);
			printf("Expand $\n");
		}
		else if (parser.qoute_state == 0 && line[i] == ' ')
		{
			// init new word
			word = ft_lst_groupword(&parser.cur_word);
			printf("word: %s\n", word);
		}
		else if (!tmp)
		{
			// join to current word
			if (line[i] == '$')
			{
				i += get_dollar(&parser, &line[i]);
				printf("Expand $\n");
				
			}
			else
				add_char(&parser, line[i]);
		}
		i++;
	}
	word = ft_lst_groupword(&parser.cur_word);
	printf("word: %s\n", word);
	if (parser.qoute_state != 0)
		printf(RED"Error: qoute not closed\n"RESET);
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
		free(tmp);
	}
	str[i] = '\0';
	return (str);
}


//// tommorrow i will add env value to current word
/// @brief 
/// @param parser 
/// @param line 
/// @return 
int		get_dollar(t_parser *parser, char *line)
{
	int i;
	int size;
	char	*tmp;
	char	*val;

	i = 0;
	while (line [i] && line[i + 1] && ft_isalnum(line[i + 1]))
		i++;
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