/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:01:03 by lkaewsae          #+#    #+#             */
/*   Updated: 2023/02/19 17:46:32 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtin.h"


// check input =
// if there is no argument env have to sort but still the same env
// ex. export p=p -> env
// if we have valuable just change value if not will add new value
// new creat case (env in env)
//

// ft_export(char)


// do it in main
int	ft_export(t_cmd *cmd, t_shell *shell)
{
	// how to export  :)
	char	**s_arg;
	char	i;
	char	*key;
	char	*content;
	static	int		times;

	i = 1;
	while(cmd->argval[i])
	{
		if (cmd->argval[i][0] == '\0')
			exit(1);
		content = ft_strchr(cmd->argval[i],'=');

		if (content != NULL && content[0] != '\0')
		{
			key = ft_substr(cmd->argval[i], 0, &content[1] -  cmd->argval[i]);
			dprintf(2,RED"Key : %s\n", key);	
			dprintf(2,GREEN"Content :%s\n", &content[1]);
			free(key);
		}
		char *envi;
		int j=0;
		while (shell->env[j] && key != NULL)
		{
			envi = ft_strnstr(shell->env[j], key, ft_strlen(key));
			if (envi != NULL)
				break;
			j++;
			printf("%s\n", envi);
		}
		char *tmp;

		dprintf(2, "%s\n", envi);
		if (envi != NULL)
		{
			tmp = envi;
			shell->env[i] = ft_strjoin("",cmd->argval[i]);
			printf("%s\n",shell->env[i]);
			free(envi);
			i++;
		}
		if (envi == NULL)
		{
			dprintf(2,RED"HELO\n"RESET);
			// shell->env = ft_str2d_addmem(shell->env, cmd->argval[i]);
		}
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
	ret[i] = new_str;
	i++;
	ret[i] = NULL;
	// free(tmp);
	return (ret);
}