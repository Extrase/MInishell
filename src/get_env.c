/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:30:47 by thenry            #+#    #+#             */
/*   Updated: 2023/10/23 20:45:18 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	*get_mini_env(char **env)
{
	t_mini	*mini;
	t_mini	*new;
	int		i;

	mini = NULL;
	new = NULL;
	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new = ft_mini_new(env[i]);
		ft_mini_add_back(&mini, new);
		i++;
	}
	return (mini);
}

void	print_env(t_mini *mini)
{
	t_mini	*tmp;

	tmp = mini;
	while (tmp)
	{
		printf("%s\n", tmp->var);
		tmp = tmp->next;
	}
}

t_mini	*ft_mini_last(t_mini *a)
{
	if (a == NULL)
		return (NULL);
	while (a->next)
		a = a->next;
	return (a);
}

t_mini	*ft_mini_new(char *var)
{
	t_mini	*new;

	new = malloc(sizeof(t_mini));
	if (!new)
		return (NULL);
	new->var = ft_strdup(var);
	new->next = NULL;
	return (new);
}

void	ft_mini_add_back(t_mini **a, t_mini *new)
{
	t_mini	*tmp;

	if (*a == NULL)
	{
		*a = new;
		return ;
	}
	tmp = ft_mini_last(*a);
	tmp->next = new;
}
