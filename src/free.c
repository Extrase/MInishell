/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:49:37 by thenry            #+#    #+#             */
/*   Updated: 2023/11/02 18:22:11 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lst_clear_fl(t_first_lst **list)
{
	t_first_lst	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free(*list);
		(*list) = tmp;
	}
}

void	ft_lst_clear_sl(t_second_lst **list)
{
	t_second_lst	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		if ((*list)->token)
			free((*list)->token);
		free(*list);
		(*list) = tmp;
	}
}

void	ft_lst_clear_env(t_mini **list)
{
	t_mini	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->var);
		free(*list);
		(*list) = tmp;
	}
}

void	ft_lst_clear_cmds(t_cmds **list, int ncmds)
{
	int	i;

	i = 0;
	while (i < ncmds)
	{
		free((*list)[i].cmd);
		i++;
	}
	free(*list);
}

char	*ft_join_and_free(char *reserve, char *buff)
{
	char	*tmp;

	if (!reserve)
		return (buff);
	tmp = ft_strjoin(reserve, buff);
	free(reserve);
	return (tmp);
}
