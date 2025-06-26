/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diavolo <diavolo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:16:30 by diavolo           #+#    #+#             */
/*   Updated: 2023/11/04 18:39:56 by diavolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_make_thing(t_cmds *data_exec, t_data *data, int read_pipe,
		int write_pipe)
{
	char	**str;
	char	*path;
	char	**env;

	str = ft_split(data_exec->cmd, ' ');
	path = ft_path_bin(str[0], data_exec->mini_env);
	if (!path || !str || read_pipe == -1)
		gain_line(path, str, data_exec, data);
	if (write_pipe != 1 && write_pipe != -1)
	{
		dup2(write_pipe, STDOUT_FILENO);
		close(write_pipe);
	}
	if (read_pipe != 0 && read_pipe != -1)
	{
		dup2(read_pipe, STDIN_FILENO);
		close(read_pipe);
	}
	env = make_env(data_exec->mini_env);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(path, str, env);
	(ft_free_int(data, &data_exec, -1), ft_free_tabx2(env));
	exit(-1);
}

void	ft_make_thing_two(t_cmds *data_exec, t_data *data, int read_pipe,
		int write_pipe)
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
	{
		dup2(write_pipe, STDOUT_FILENO);
		close(write_pipe);
	}
	if (read_pipe != 0 && read_pipe != -1)
	{
		dup2(read_pipe, STDIN_FILENO);
		close(read_pipe);
	}
	env = make_env(data_exec->mini_env);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(path, arr, env);
	(ft_free_int(data, &data_exec, -1), ft_free_tabx2(env));
	exit(-1);
}

void	ft_first_pipe(t_cmds *data_exec, t_data *data)
{
	int	j;

	j = 0;
	while (++j < data->ncmd)
		ft_close_fd(data->pipe[j]);
	gain_first(data_exec, data);
	if (data_exec->outfile != -1 && data_exec->outfile != 1)
	{
		close(data->pipe[0][1]);
		if ((ft_verif_space(data_exec->cmd) == 1))
			ft_make_thing(data_exec, data, data_exec->infile,
				data_exec->outfile);
		else
			ft_make_thing_two(data_exec, data, data_exec->infile,
				data_exec->outfile);
	}
	else
	{
		close(data_exec->outfile);
		if ((ft_verif_space(data_exec->cmd) == 1))
			ft_make_thing(data_exec, data, data_exec->infile, data->pipe[0][1]);
		else
			ft_make_thing_two(data_exec, data, data_exec->infile,
				data->pipe[0][1]);
	}
}

void	ft_inter_pipe(t_cmds *data_exec, int i, t_data *data)
{
	int	j;

	j = -1;
	while (++j < data->ncmd)
		if (j != i && j != (i - 1))
			ft_close_fd(data->pipe[j]);
	gain_inter(data_exec, data, i);
	if (data_exec->infile != -1 && data_exec->infile != 0)
	{
		close(data->pipe[i - 1][0]);
		if ((ft_verif_space(data_exec->cmd) == 1))
			ft_make_thing(data_exec, data, data_exec->infile, data->pipe[i][1]);
		else
			ft_make_thing_two(data_exec, data, data_exec->infile,
				data->pipe[i][1]);
	}
	else if (data_exec->outfile != -1 && data_exec->outfile != 1)
		gain_inter_two(data_exec, data, i);
	else
		close(data_exec->infile);
	if ((ft_verif_space(data_exec->cmd) == 1))
		ft_make_thing(data_exec, data, data->pipe[i - 1][0], data->pipe[i][1]);
	else
		ft_make_thing_two(data_exec, data, data->pipe[i - 1][0],
			data->pipe[i][1]);
}

void	ft_last_pipe(t_cmds *data_exec, int i, t_data *data)
{
	int	j;

	ft_close_fd(data->pipe[i]);
	j = -1;
	while (++j < (i - 1))
		ft_close_fd(data->pipe[j]);
	gain_last(data_exec, data, i);
	if (data_exec->infile != -1 && data_exec->infile != 0)
	{
		close(data->pipe[i - 1][0]);
		if ((ft_verif_space(data_exec->cmd) == 1))
			ft_make_thing(data_exec, data, data_exec->infile,
				data_exec->outfile);
		else
			ft_make_thing_two(data_exec, data, data_exec->infile,
				data_exec->outfile);
	}
	else
		close(data_exec->infile);
	if ((ft_verif_space(data_exec->cmd) == 1))
		ft_make_thing(data_exec, data, data->pipe[i - 1][0],
			data_exec->outfile);
	else
		ft_make_thing_two(data_exec, data, data->pipe[i - 1][0],
			data_exec->outfile);
}
