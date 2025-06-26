/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderkaou <mderkaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:53:58 by mderkaou          #+#    #+#             */
/*   Updated: 2023/11/02 15:45:28 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lst_get_last(t_list *stock)
{
	t_list	*copy;

	copy = stock;
	while (copy && copy->next)
		copy = copy->next;
	return (copy);
}

int	found_newline(t_list *stock)
{
	int		i;
	t_list	*copy;

	i = 0;
	if (stock == NULL)
		return (0);
	copy = ft_lst_get_last(stock);
	while (copy->content[i])
	{
		if (copy->content[i] == '\n')
			return (1);
		++i;
	}
	return (0);
}

void	free_stock(t_list *stock)
{
	t_list	*next;
	t_list	*tmp;

	tmp = stock;
	while (tmp)
	{
		free(tmp->content);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void	generate_line(char **line, t_list *stock)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (stock)
	{
		i = 0;
		while (stock->content[i])
		{
			if (stock->content[i] == '\n')
			{
				++len;
				break ;
			}
			++i;
			++len;
		}
		stock = stock->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}
