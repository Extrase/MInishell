/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diavolo <diavolo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 23:13:37 by thenry            #+#    #+#             */
/*   Updated: 2023/11/02 15:40:29 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_mini **mini_env, char *var)
{
	t_mini	*tmp;

	tmp = *mini_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, var, ft_strlen(var)) == 0)
			return (tmp->var + ft_strlen(var));
		tmp = tmp->next;
	}
	return (NULL);
}

int	switch_dir(t_mini **mini_env, char *old, char *pwd, int fd)
{
	char	*tmp;
	char	*tmpp;

	tmp = ft_strjoin("export OLDPWD=", old);
	tmpp = ft_strjoin("export PWD=", pwd);
	unset_builtin(mini_env, "unset OLDPWD");
	export_builtin(mini_env, tmp, fd);
	unset_builtin(mini_env, "unset PWD");
	export_builtin(mini_env, tmpp, fd);
	free(tmp);
	free(tmpp);
	return (0);
}

int	cd_builtin(t_mini **mini_env, char **cmds, int fd)
{
	char	*path;

	if (cmds[0] && ft_strcmp(cmds[0], "cd") == 0 && !cmds[1])
	{
		ft_free_tabx2(cmds);
		return (cd_home(mini_env, fd));
	}
	else if (cmds[0] && ft_strcmp(cmds[0], "cd") == 0 && cmds[1])
	{
		path = ft_strdup(cmds[1]);
		ft_free_tabx2(cmds);
		if (ft_strncmp(path, "-", ft_strlen(path)) == 0)
			return (free(path), cd_old(mini_env, fd));
		else if (ft_strncmp(path, "~", ft_strlen(path)) == 0)
			return (free(path), cd_home(mini_env, fd));
		else
			return (cd_path(mini_env, path, fd));
	}
	else if (cmds[1] && cmds[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		g_exit_status = 1;
	}
	ft_free_tabx2(cmds);
	return (g_exit_status);
}
