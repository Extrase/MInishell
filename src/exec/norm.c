/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diavolo <diavolo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:43:23 by diavolo           #+#    #+#             */
/*   Updated: 2023/11/08 20:37:15 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	gain_line(char *path, char **str, t_cmds *data_exec, t_data *data)
{
	if (path)
	{
		perror(path);
		free(path);
	}
	if (str)
	{
		printf("minishell : %s : command not found\n", str[0]);
		ft_free_tabx2(str);
	}
	else
		printf("minishell : %s : command not found\n", data_exec->cmd);
	ft_free_int(data, &data_exec, 2);
	exit(EXIT_FAILURE);
}

void	gain_first_two(t_cmds *data_exec, t_data *data)
{
	close(data->pipe[0][0]);
	close(data->pipe[0][1]);
	exec_builtin(data_exec, data, data_exec->outfile, -1);
	close(data_exec->infile);
	close(data_exec->outfile);
	ft_free_int(data, &data_exec, 2);
	exit(0);
}

void	gain_first(t_cmds *data_exec, t_data *data)
{
	if (data_exec->infile == -1)
	{
		close(data->pipe[0][1]);
		close(data_exec->outfile);
		ft_free_int(data, &data_exec, -1);
		close(data->pipe[0][0]);
		exit(EXIT_FAILURE);
	}
	if (data_exec->path && data_exec->outfile != -1 && data_exec->outfile != 1)
		gain_first_two(data_exec, data);
	if (data_exec->path)
	{
		exec_builtin(data_exec, data, data->pipe[0][1], -1);
		close(data_exec->outfile);
		close(data_exec->infile);
		close(data->pipe[0][0]);
		close(data->pipe[0][1]);
		ft_free_int(data, &data_exec, -1);
		exit(0);
	}
	close(data->pipe[0][0]);
}

void	gain_inter_built(t_cmds *data_exec, t_data *data, int i)
{
	close(data->pipe[i][1]);
	close(data->pipe[i][0]);
	exec_builtin(data_exec, data, data_exec->outfile, -1);
	if (data_exec->infile != -1 && data_exec->infile != 0)
		close(data_exec->infile);
	close(data_exec->outfile);
	close(data->pipe[i - 1][0]);
	ft_free_int(data, &data_exec, -1);
	exit(0);
}

void	gain_inter(t_cmds *data_exec, t_data *data, int i)
{
	if (data_exec->path && data_exec->outfile != -1 && data_exec->outfile != 1)
		gain_inter_built(data_exec, data, i);
	if (data_exec->path)
	{
		close(data_exec->outfile);
		exec_builtin(data_exec, data, data->pipe[i][1], -1);
		close(data->pipe[i][1]);
		close(data->pipe[i][0]);
		close(data->pipe[i - 1][0]);
		ft_free_int(data, &data_exec, -1);
		exit(0);
	}
	close(data->pipe[i][0]);
	if (data_exec->infile != -1 && data_exec->infile != 0
		&& data_exec->outfile != -1 && data_exec->outfile != 1)
	{
		close(data->pipe[i - 1][0]);
		close(data->pipe[i][1]);
		if ((ft_verif_space(data_exec->cmd) == 1))
			ft_make_thing(data_exec, data, data_exec->infile,
				data_exec->outfile);
		else
			ft_make_thing_two(data_exec, data, data_exec->infile,
				data_exec->outfile);
	}
}
