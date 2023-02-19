/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_from_key.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:52:59 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/20 02:00:34 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

char	*get_env_from_key(char *key, t_shell *shell)
{
	char	*ret;
	char	*tmp_key;
	char	*val;
	int		key_len;
	int		i;

	key_len = create_tmp_key(&tmp_key, key);
	i = 0;
	while (shell->env[i])
	{
		val = ft_strnstr(shell->env[i], tmp_key, key_len);
		if (val)
		{
			ret = ft_strdup(shell->env[i] + key_len);
			free(tmp_key);
			return (ret);
		}
		i++;
	}
	free(tmp_key);
	return (NULL);
}

int		create_tmp_key(char **buf, char *key)
{
	if (!key || !buf)
		return (-1);
	*buf = ft_strjoin(key, "=");
	if (!buf)
		return (-1);
	return ((int)ft_strlen(*buf));
}