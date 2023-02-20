/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:04:27 by nwattana          #+#    #+#             */
/*   Updated: 2023/02/20 17:04:16 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/debug.h"

static int		setpwd(t_shell *shell);
static int		setcwd(t_shell *shell, char *tmp);
char	*to_home(t_cmd *cmd , t_shell *shell);
// SET OLDPWD = CURRENT PWD
// change directory 
// SET PWD = NEW PWD if have PWD
// OLD pwd will spawn after cd
int		ft_cd(t_cmd *cmd, t_shell *shell)
{
	char	*tmp;

	// temporary keep curdir
	if (cmd->argcount == 1)
	{
		tmp = to_home(cmd, shell);
		if (!tmp)
			return (ft_putendl_fd("minishell: cd: HOME not set", 2), 1);
		add_argument(cmd, tmp);
	}
	else
	{
		tmp = malloc(sizeof(char) * PATH_MAX);
		tmp = getcwd(tmp, PATH_MAX);
	}
	// change dir 
	if (chdir(cmd->argval[1]) != 0)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(cmd->argval[1], 2);
		free(tmp);
		cmd->cmd_pre_exit_status = 1;
		return (1);
	}
	setcwd(shell, tmp);
	setpwd(shell);
	return (0);
}

static int		setcwd(t_shell *shell, char *tmp)
{
	char	*tmp2;
	t_cmd	*handoncmd;
	
	tmp2 = ft_strjoin("OLDPWD=", tmp);
	handoncmd = cmd_hand_gen("export", tmp2);
	ft_export(handoncmd, shell);
	free(tmp2);
	free(shell->pwd);
	shell->pwd=tmp;
	tmp = NULL;
	tmp2 = NULL;
	cmd_clear(handoncmd);
	return (0);
}

static int		setpwd(t_shell *shell)
{
	char *tmp;
	char *tmp2;
	t_cmd *handoncmd;
	
	if (check_env_valid_key("PWD", shell) > 0)
	{
		tmp = getcwd(tmp, PATH_MAX);
		tmp2 = ft_strjoin("PWD=", tmp);
		handoncmd = cmd_hand_gen("export", tmp2);
		ft_export(handoncmd, shell);
		free(tmp2);
		free(tmp);
		cmd_clear(handoncmd);
	}
	return (0);
}

int		check_env_valid_key(char *key, t_shell *sh)
{
	char	*tmp;
	char	*valid_key;
	int		i;
	int		key_len;

	i = 0;
	valid_key = ft_strjoin(key, "=");
	key_len = ft_strlen(valid_key);
	while (sh->env[i])
	{
		if (ft_strnstr(sh->env[i], valid_key, key_len))
		{
			free(valid_key);
			return (i);
		}
		i++;
	}
	free(valid_key);
	return (0);
}

char	*to_home(t_cmd *cmd , t_shell *shell)
{
	char	*ret;

	ret = get_env_from_key("HOME", shell);
	if (!ret)
	{
		return (NULL);
	}
	return (ret);
}