/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:57:25 by mderkaou          #+#    #+#             */
/*   Updated: 2023/11/08 18:47:38 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	here_comp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*st1;
	unsigned char	*st2;

	i = 0;
	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	while ((st1[i] || st2[i]) && i < n)
	{
		if (st1[i] != st2[i])
			return (st1[i] - st2[i]);
		i++;
	}
	i++;
	if (st1[i] != '\0')
	{
		return (1);
	}
	return (0);
}

int	open_read_doc(t_cmds *data_exec)
{
	data_exec->infile = open(".tmp_5546412sdfsdg46351g5fs646129",
			O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (data_exec->infile == -1)
		return (ft_putstr_fd("fd error\n", 2), 1);
	return (0);
}

void	delimiter_error(char *limiter)
{
	write(2, "\n", 1);
	ft_putstr_fd("minishell: warning: here-document ", 2);
	ft_putstr_fd("delimited by end-of-file (wanted \'", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("\')\n", 2);
}

void	read_doc(t_cmds *data_exec, char *limiter)
{
	char	*line;

	if (open_read_doc(data_exec) == 1)
		return ;
	while (1)
	{
		if (g_exit_status == 130)
		{
			get_next_line(-1);
			break ;
		}
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (line)
		{
			if (here_gain(line, limiter, data_exec) == 1)
				break ;
		}
		else
		{
			delimiter_error(limiter);
			break ;
		}
	}
}

void	here_doc(t_cmds *data_exec, char *limiter)
{
	int	fd;

	fd = 0;
	if (data_exec->infile == INT_MAX)
	{
		read_doc(data_exec, limiter);
		fd = open(".tmp_5546412sdfsdg46351g5fs646129", O_RDONLY);
		dup2(fd, data_exec->infile);
		close(fd);
	}
}
