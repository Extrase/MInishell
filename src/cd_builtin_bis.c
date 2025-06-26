/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:39:11 by thenry            #+#    #+#             */
/*   Updated: 2023/11/05 16:43:44 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_old(t_mini **mini_env, int fd)
{
	char	*old;
	char	*pwd;

	old = get_env(mini_env, "OLDPWD=");
	pwd = get_env(mini_env, "PWD=");
	if (!old)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		g_exit_status = 1;
		return (g_exit_status);
	}
	if (chdir(old))
	{
		ft_putstr_fd("minishell: cd: error\n", 2);
		g_exit_status = 1;
		return (g_exit_status);
	}
	ft_putstr_fd(old, 1);
	ft_putstr_fd("\n", 1);
	switch_dir(mini_env, pwd, old, fd);
	g_exit_status = 0;
	return (g_exit_status);
}

int	cd_home(t_mini **mini_env, int fd)
{
	char	*pwd;
	char	*home;

	pwd = get_env(mini_env, "PWD=");
	home = get_env(mini_env, "HOME=");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		g_exit_status = 1;
		return (g_exit_status);
	}
	if (chdir(home))
	{
		ft_putstr_fd("minishell: cd: error\n", 2);
		g_exit_status = 1;
		return (g_exit_status);
	}
	switch_dir(mini_env, pwd, home, fd);
	g_exit_status = 0;
	return (g_exit_status);
}

int	cd_path(t_mini **mini_env, char *path, int fd)
{
	char	*pwd;
	char	*tmp;

	pwd = getcwd(NULL, 0);
	if (chdir(path))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_exit_status = 1;
		free(path);
		free(pwd);
		return (g_exit_status);
	}
	tmp = getcwd(NULL, 0);
	switch_dir(mini_env, pwd, tmp, fd);
	if (pwd && tmp)
	{
		free(pwd);
		free(tmp);
	}
	free(path);
	g_exit_status = 0;
	return (g_exit_status);
}
