/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaewsae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 01:43:23 by lkaewsae          #+#    #+#             */
/*   Updated: 2023/02/21 01:44:54 by lkaewsae         ###   ########.fr       */
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
