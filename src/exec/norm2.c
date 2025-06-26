/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:01:28 by diavolo           #+#    #+#             */
/*   Updated: 2023/11/08 18:49:28 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_gain(t_data *data, int alacon)
{
	if (data->second_list)
		ft_lst_clear_sl(&(data)->second_list);
	if (data->first_list)
		ft_lst_clear_fl(&(data)->first_list);
	if (data->prompt)
		free(data->prompt);
	if (data->mini_env)
		ft_lst_clear_env(&(data)->mini_env);
	if (data->cmd_list)
		ft_lst_clear_cmds(&(data)->cmd_list, alacon);
}

void	gain_inter_two(t_cmds *data_exec, t_data *data, int i)
{
	close(data_exec->infile);
	close(data->pipe[i][1]);
	if ((ft_verif_space(data_exec->cmd) == 1))
		ft_make_thing(data_exec, data, data->pipe[i - 1][0],
			data_exec->outfile);
	else
		ft_make_thing_two(data_exec, data, data->pipe[i - 1][0],
			data_exec->outfile);
}

void	gain_last(t_cmds *data_exec, t_data *data, int i)
{
	close(data->pipe[i - 1][1]);
	if (data_exec->path)
	{
		close(data_exec->infile);
		close(data->pipe[i - 1][0]);
		exec_builtin(data_exec, data, data_exec->outfile, -1);
		close(data_exec->outfile);
		ft_free_int(data, &data_exec, -1);
		exit(0);
	}
}

int	here_gain(char *line, char *limiter, t_cmds *data_exec)
{
	if (line && here_comp(line, limiter, ft_strlen(limiter)) == 0)
	{
		free(line);
		get_next_line(-1);
		return (1);
	}
	write(data_exec->infile, line, ft_strlen(line));
	free(line);
	return (0);
}
