/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diavolo <diavolo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:50:03 by mderkaou          #+#    #+#             */
/*   Updated: 2023/11/04 16:18:13 by diavolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	add_buff(t_list **stock, char *buff, int readed)
{
	t_list	*copy;
	t_list	*last;
	int		i;

	i = 0;
	copy = malloc(sizeof(t_list));
	if (!copy)
		return ;
	copy->next = NULL;
	copy->content = (malloc(sizeof(char) * (readed + 1)));
	if (!copy->content)
		return ;
	while (buff[i] && i < readed)
	{
		copy->content[i] = buff[i];
		++i;
	}
	copy->content[i] = '\0';
	if (*stock == NULL)
	{
		*stock = copy;
		return ;
	}
	last = ft_lst_get_last(*stock);
	last->next = copy;
}

void	ft_read(int fd, t_list **stock)
{
	char	*buff;
	ssize_t	readed;

	readed = 1;
	while (found_newline(*stock) == 0 && readed != 0)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return ;
		readed = read(fd, buff, BUFFER_SIZE);
		if ((*stock == NULL && readed == 0) || readed == -1)
		{
			free(buff);
			return ;
		}
		buff[readed] = '\0';
		add_buff(stock, buff, readed);
		free(buff);
	}
}

void	extract_line(t_list *stock, char **line)
{
	int	i;
	int	o;

	i = 0;
	if (!stock)
		return ;
	generate_line(line, stock);
	if (*line == NULL)
		return ;
	while (stock)
	{
		o = 0;
		while (stock->content[o])
		{
			if (stock->content[o] == '\n')
			{
				(*line)[i++] = stock->content[o];
				break ;
			}
			(*line)[i++] = stock->content[o++];
		}
		stock = stock->next;
	}
	(*line)[i] = '\0';
}

void	clean_stock(t_list **stock)
{
	t_list	*last;
	t_list	*stock_last;
	int		i;
	int		j;

	i = 0;
	j = 0;
	stock_last = malloc(sizeof(t_list));
	if (*stock == NULL || stock_last == NULL)
		return ;
	stock_last->next = NULL;
	last = ft_lst_get_last(*stock);
	while (last->content[i] && last->content[i] != '\n')
		++i;
	i += (last->content[i] && last->content[i] == '\n');
	stock_last->content = malloc(sizeof(char) * ((ft_strlen(last->content) - i)
				+ 1));
	if (!stock_last->content)
		return ;
	while (last->content[i])
		stock_last->content[j++] = last->content[i++];
	stock_last->content[j] = '\0';
	free_stock(*stock);
	*stock = stock_last;
}

char	*get_next_line(int fd)
{
	static t_list	*stock = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free_stock(stock);
		stock = NULL;
		return (NULL);
	}
	ft_read(fd, &stock);
	if (stock == NULL)
		return (NULL);
	extract_line(stock, &line);
	clean_stock(&stock);
	if (line == NULL || line[0] == '\0')
	{
		free_stock(stock);
		stock = NULL;
		return (free(line), NULL);
	}
	return (line);
}

// int	main(void)
// {
// 	char	*test;
// 	int		fd;

// 	fd = open("text.txt", O_RDONLY);
// 	test = get_next_line(fd);
// 	while (test)
// 	{
// 		printf("%s", test);
// 		free(test);
// 		test = get_next_line(fd);
// 	}
// 	return (0);
// }
