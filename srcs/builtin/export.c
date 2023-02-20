/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:01:03 by lkaewsae          #+#    #+#             */
/*   Updated: 2023/02/20 17:34:42 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/my_builtin.h"

// check input =
// if there is no argument env have to sort but still the same env
// ex. export p=p -> env
// if we have valuable just change value if not will add new value
// new creat case (env in env)
// ft_export(char)
// do it in main
int	ft_export(t_cmd *cmd, t_shell *shell)
{
	char	**s_arg;
	char	i;
	char	*key;
	char	*content;
	char	*envi;

	i = 1;
	if (cmd->argcount == 1)
		return (put_sort_env(shell));
	while (cmd->argval[i])
	{
		if (cmd->argval[i][0] == '\0')
			return (1);
		content = ft_strchr(cmd->argval[i] , '=');
		if (content == NULL)
		{
			i++;
			continue ;
		}
		
		if (content[0] != '\0')
		{
			key = ft_substr(cmd->argval[i], 0, &content[1] -  cmd->argval[i]);
			free(key);
		}

		int j;
		j = 0;
		while (shell->env[j] && key != NULL)
		{
			envi = ft_strnstr(shell->env[j], key, ft_strlen(key));
			if (envi != NULL)
				break;
			j++;
		}

		char *tmp;
		if (envi != NULL)
		{
			tmp = envi;
			shell->env[j] = ft_strdup(cmd->argval[i]);
			free(envi);
			j++;
		}

		if (envi == NULL)
		{
			shell->env = ft_str2d_addmem(shell->env, cmd->argval[i]);
		}
		i++;
	}
	return (0);
}

char	**ft_str2d_addmem(char **str, char *new_str)
{
	char	**tmp;
	int		size;
	char	**ret;
	int		i;

	size = 0;
	tmp = str;
	while (str[size] != NULL)
	{
		size++;
	}
	ret = malloc(sizeof(char *) * (size + 2));
	i = 0;
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = ft_strdup(new_str);
	i++;
	ret[i] = NULL;
	free(tmp);
	str = NULL;
	return (ret);
}