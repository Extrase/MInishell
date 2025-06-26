/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diavolo <diavolo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:25:22 by mderkaou          #+#    #+#             */
/*   Updated: 2023/11/08 20:36:40 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_one(t_cmds *data_exec, t_data *data, int read_pipe, int write_pipe)
{
	char	**str;
	char	*path;
	char	**env;

	str = ft_split(data_exec->cmd, ' ');
	path = ft_path_bin(str[0], data_exec->mini_env);
	if (!path || !str || read_pipe == -1)
		gain_line(path, str, data_exec, data);
	if (write_pipe != 1 && write_pipe != -1)
		dup2(write_pipe, STDOUT_FILENO);
	if (read_pipe != 0 && read_pipe != -1)
		dup2(read_pipe, STDIN_FILENO);
	if (write_pipe != 1 && write_pipe != -1)
		close(write_pipe);
	if (read_pipe != 0 && read_pipe != -1)
		close(read_pipe);
	env = make_env(data_exec->mini_env);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(path, str, env);
	(ft_free_int(data, &data_exec, 2), ft_free_tabx2(env));
	exit(-1);
}

void	exec_two(t_cmds *data_exec, t_data *data, int read_pipe, int write_pipe)
{
	char	*path;
	char	*arr[2];
	char	**env;

	path = ft_path_bin(data_exec->cmd, data_exec->mini_env);
	if (!path || read_pipe == -1)
		gain_line(path, NULL, data_exec, data);
	arr[0] = path;
	arr[1] = NULL;
	if (write_pipe != 1 && write_pipe != -1)
		dup2(write_pipe, STDOUT_FILENO);
	if (read_pipe != 0 && read_pipe != -1)
		dup2(read_pipe, STDIN_FILENO);
	if (write_pipe != 1 && write_pipe != -1)
		close(write_pipe);
	if (read_pipe != 0 && read_pipe != -1)
		close(read_pipe);
	env = make_env(data_exec->mini_env);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(path, arr, env);
	(ft_free_int(data, &data_exec, 2), ft_free_tabx2(env));
	exit(-1);
}
