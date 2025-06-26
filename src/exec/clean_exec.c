/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diavolo <diavolo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:29:36 by diavolo           #+#    #+#             */
/*   Updated: 2023/11/02 20:04:00 by diavolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_tabx2(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		if (str[i])
		{
			while (str[i])
			{
				free(str[i]);
				i++;
			}
		}
		free(str);
	}
	return ;
}

void	ft_free_int(t_data *data, t_cmds **data_exec, int o)
{
	int	i;
	int	alacon;

	i = -1;
	alacon = 0;
	if (data->second_list)
		alacon = count_cmd(data->second_list);
	(void)data_exec;
	if (o != 1 && data)
		clear_gain(data, alacon);
	if (data && o != 2)
	{
		while (++i < data->ncmd)
		{
			if (data->pipe[i])
				free(data->pipe[i]);
		}
		if (data->pipe)
			free(data->pipe);
	}
}

void	ft_close_all(t_cmds **data_exec, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->ncmd)
		ft_close_fd(data->pipe[i]);
	i = -1;
	while (++i < data->ncmd)
	{
		if ((*data_exec)[i].outfile != 1 && (*data_exec)[i].outfile != -1)
			close((*data_exec)[i].outfile);
		if ((*data_exec)[i].infile != 0 && (*data_exec)[i].infile != -1)
			close((*data_exec)[i].infile);
	}
}

void	ft_close_fd(int *fd)
{
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
}

int	ft_verif_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}
