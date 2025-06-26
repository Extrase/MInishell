/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diavolo <diavolo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:29:51 by thenry            #+#    #+#             */
/*   Updated: 2023/11/08 20:03:29 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clean_echo(char *cmds)
{
	if (ft_strchr(cmds, '\'') && ft_strchr(cmds, '\"'))
	{
		if (ft_strchr(cmds, '\'') > ft_strchr(cmds, '\"'))
			cmds = remove_double_quotes(cmds, 0, 0);
		else if (ft_strchr(cmds, '\'') < ft_strchr(cmds, '\"'))
			cmds = remove_single_quotes(cmds, 0, 0);
		return (cmds);
	}
	cmds = remove_double_quotes(cmds, 0, 0);
	cmds = remove_single_quotes(cmds, 0, 0);
	return (cmds);
}

int	echo_builtin(char *cmds, int fd)
{
	int	i;

	i = 0;
	cmds = clean_echo(cmds);
	g_exit_status = 0;
	if (ft_strncmp(cmds, "echo -n ", 8) == 0)
	{
		i += 8;
		while (cmds[i])
			ft_putchar_fd(cmds[i++], fd);
	}
	else if (ft_strncmp(cmds, "echo -n", 7) == 0)
		return (g_exit_status);
	else if (ft_strncmp(cmds, "echo ", 5) == 0)
	{
		i += 5;
		while (cmds[i])
			ft_putchar_fd(cmds[i++], fd);
		ft_putchar_fd('\n', fd);
	}
	else
		ft_putchar_fd('\n', fd);
	return (g_exit_status);
}
