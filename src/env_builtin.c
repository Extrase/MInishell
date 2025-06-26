/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diavolo <diavolo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:56:50 by thenry            #+#    #+#             */
/*   Updated: 2023/11/06 15:37:00 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// A REFAIRE

int	env_error(char *cmds)
{
	ft_putstr_fd("env: '", 2);
	ft_putstr_fd(cmds + 4, 2);
	ft_putstr_fd("': No such file or directory\n", 2);
	g_exit_status = 127;
	return (g_exit_status);
}

int	env_builtin(t_mini **mini, char *cmds, int fd)
{
	t_mini	*tmp;

	tmp = *mini;
	g_exit_status = 0;
	if (!tmp)
		ft_putchar_fd('\n', fd);
	else if (ft_strcmp(cmds, "env"))
		return (env_error(cmds));
	else
	{
		while (tmp)
		{
			if (ft_strchr(tmp->var, '='))
			{
				ft_putstr_fd(tmp->var, fd);
				ft_putchar_fd('\n', fd);
			}
			tmp = tmp->next;
		}
	}
	return (g_exit_status);
}
