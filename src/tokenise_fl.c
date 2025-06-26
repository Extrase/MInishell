/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_fl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:14:03 by thenry            #+#    #+#             */
/*   Updated: 2023/11/02 17:16:37 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_first_lst	*ft_lst_last(t_first_lst *a)
{
	if (a == NULL)
		return (NULL);
	while (a->next)
		a = a->next;
	return (a);
}

t_first_lst	*ft_lst_new(char character, int in_quotes)
{
	t_first_lst	*new;

	new = malloc(sizeof(t_first_lst));
	if (!new)
		return (NULL);
	new->c = character;
	new->cs[0] = character;
	new->cs[1] = '\0';
	if (in_quotes == 1 && character != '\'')
		new->type = 0;
	else if (in_quotes == 2 && character != '\"')
		new->type = 0;
	else
		new->type = get_type(character);
	new->next = NULL;
	return (new);
}

void	ft_lst_add_back(t_first_lst **a, t_first_lst *new)
{
	t_first_lst	*tmp;

	if (*a == NULL)
	{
		*a = new;
		return ;
	}
	tmp = ft_lst_last(*a);
	tmp->next = new;
}

// 0 = FALSE | 1 = SQUOTES | 2 = DQUOTES

t_first_lst	*fill_list_tmp(char *prompt)
{
	int			i;
	t_first_lst	*list;
	t_first_lst	*new;
	int			in_quotes;

	list = NULL;
	i = 0;
	in_quotes = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'' && in_quotes == 0)
			in_quotes = 1;
		else if (prompt[i] == '\"' && in_quotes == 0)
			in_quotes = 2;
		else if (prompt[i] == '\'' && in_quotes == 1)
			in_quotes = 0;
		else if (prompt[i] == '\"' && in_quotes == 2)
			in_quotes = 0;
		new = ft_lst_new(prompt[i], in_quotes);
		ft_lst_add_back(&list, new);
		i++;
	}
	return (list);
}

void	print_lst(t_first_lst *list)
{
	t_first_lst	*tmp;

	tmp = list;
	while (tmp)
	{
		printf("char = %c & type = %d\n", tmp->c, tmp->type);
		tmp = tmp->next;
	}
}
