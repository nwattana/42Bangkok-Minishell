/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_clear_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 01:43:23 by lkaewsae          #+#    #+#             */
/*   Updated: 2023/02/21 13:35:40 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	clean_parser(void *parser)
{
	t_parser	*pr;

	pr = (t_parser *)parser;
	clean_lexel(pr->tmp_lexel);
}

void	clean_lexel(void *lexel)
{
	t_lexel		*lex;

	lex = (t_lexel *)lexel;
	if (lex != NULL)
	{
		if (lex->str)
			free(lex->str);
		lex->str = NULL;
		free(lex->str);
		lex = NULL;
	}
}

void	clear_hd(void *vtf_cmd)
{
	t_cmd	*cmd;

	if (!vtf_cmd)
		return ;
	cmd = (t_cmd *)vtf_cmd;
	if (cmd->here_doc_status)
	{
		unlink(cmd->heredoc_filename);
		free(cmd->heredoc_filename);
		cmd->heredoc_filename = NULL;
	}
	cmd->here_doc_status = 0;
}

char	**ft_str2drelloc_free(char **str, int size)
{
	char	**new_str;
	int		i;

	i = 0;
	new_str = ft_calloc(sizeof(char *), size);
	while (i < (size - 10))
	{
		new_str[i] = ft_strdup(str[i]);
		i++;
	}
	ft_str2diter(str, &free);
	free(str);
	return (new_str);
}
// clear here doc file
// and set here doc status to 0
