/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaewsae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 01:28:08 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/20 21:12:54 by lkaewsae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int		check_reserverd(t_parser *parser, char *line, t_shell *shell);
static void		loop_add_char(t_parser *parser, char *val);

int	get_dollar(t_parser *parser, char *line, t_shell *shell)
{
	int		i;
	int		size;
	char	*tmp;
	char	*val;

	i = 0;
	while (line [i] && line[i + 1] && ft_isalnum(line[i + 1]))
		i++;
	if (i == 0)
		return (check_reserverd(parser, line, shell));
	if (i > 0)
	{
		tmp = ft_substr(line, 1, i);
		val = get_env_from_key(tmp, shell);
	}
	loop_add_char(parser, val);
	free(val);
	free(tmp);
	return (i);
}

static void	loop_add_char(t_parser *parser, char *val)
{
	int		size;

	size = 0;
	while (val != NULL && val[size])
	{
		add_char(parser, val[size]);
		size++;
	}
}

static int	check_reserverd(t_parser *parser, char *line, t_shell *shell)
{
	char	*tmp;
	int		i;

	i = 0;
	if (line[1] == '$')
		tmp = ft_itoa(getpid());
	else if (line[1] == '?')
		tmp = ft_itoa(shell->last_status);
	else
		return (0);
	while (tmp[i])
	{
		add_char(parser, tmp[i]);
		i++;
	}
	free(tmp);
	return (1);
}
