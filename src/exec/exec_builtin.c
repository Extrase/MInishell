/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diavolo <diavolo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:03 by mderkaou          #+#    #+#             */
/*   Updated: 2023/11/04 18:30:52 by diavolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_builtin(t_cmds *data_exec, t_data *data, int fd, int o)
{
	(void)o;
	if (ft_strcmp(data_exec->path, "{ECHO BUILTIN}") == 0)
		echo_builtin(data_exec->cmd, fd);
	else if (ft_strcmp(data_exec->path, "{CD BUILTIN}") == 0)
		cd_builtin(&(data)->mini_env, ft_split(data_exec->cmd, ' '), fd);
	else if (ft_strcmp(data_exec->path, "{UNSET BUILTIN}") == 0)
		unset_builtin(&(data)->mini_env, data_exec->cmd);
	else if (ft_strcmp(data_exec->path, "{EXPORT BUILTIN}") == 0)
		export_builtin(&(data)->mini_env, data_exec->cmd, fd);
	else if (ft_strcmp(data_exec->path, "{PWD BUILTIN}") == 0)
		pwd_builtin(fd);
	else if (ft_strcmp(data_exec->path, "{ENV BUILTIN}") == 0)
		env_builtin(&(data)->mini_env, data_exec->cmd, fd);
	else if (ft_strcmp(data_exec->path, "{EXIT BUILTIN}") == 0)
		exit_builtin(ft_split(data_exec->cmd, ' '), data, data_exec, o);
}
