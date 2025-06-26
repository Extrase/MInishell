/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diavolo <diavolo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 15:57:38 by thenry            #+#    #+#             */
/*   Updated: 2023/11/08 20:12:43 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str) || *str != '-')
			return (1);
		str++;
	}
	return (1);
}

void	exit_gain(char **cmds, t_data *data, t_cmds *data_exec, int o)
{
	ft_putstr_fd("exit\n", 1);
	g_exit_status = 0;
	ft_free_tabx2(cmds);
	ft_free_int(data, &data_exec, o);
	exit(g_exit_status);
}

void	exit_gain_two(char **cmds, t_data *data, t_cmds *data_exec, int o)
{
	ft_putstr_fd("exit\n", 1);
	g_exit_status = ft_atoi(cmds[1]);
	ft_free_tabx2(cmds);
	ft_free_int(data, &data_exec, o);
	exit(g_exit_status);
}

int	exit_builtin(char **cmds, t_data *data, t_cmds *data_exec, int o)
{
	if (ft_strcmp(cmds[0], "exit") == 0)
	{
		if (!cmds[1])
			exit_gain(cmds, data, data_exec, o);
		else if (cmds[1] && is_numeric(cmds[1]))
		{
			if (!cmds[2])
				exit_gain_two(cmds, data, data_exec, o);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			g_exit_status = 1;
			ft_free_tabx2(cmds);
			return (g_exit_status);
		}
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		g_exit_status = 2;
		ft_free_tabx2(cmds);
		return (g_exit_status);
	}
	ft_free_tabx2(cmds);
	ft_free_int(data, &data_exec, o);
	return (g_exit_status);
}
