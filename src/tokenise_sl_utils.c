/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_sl_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:35:56 by thenry            #+#    #+#             */
/*   Updated: 2023/11/04 13:39:46 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_second_lst	*ft_second_lst_last(t_second_lst *a)
{
	if (a == NULL)
		return (NULL);
	while (a->next)
		a = a->next;
	return (a);
}

t_second_lst	*ft_second_lst_new(char *tok, int tok_type)
{
	t_second_lst	*new;

	new = malloc(sizeof(t_second_lst));
	if (!new)
		return (NULL);
	new->token = tok;
	new->token_type = tok_type;
	new->next = NULL;
	return (new);
}

void	ft_second_lst_add_back(t_second_lst **a, t_second_lst *new)
{
	t_second_lst	*tmp;

	if (*a == NULL)
	{
		*a = new;
		return ;
	}
	tmp = ft_second_lst_last(*a);
	tmp->next = new;
}

int	ft_is_op(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

void	print_second_lst(t_second_lst *list)
{
	t_second_lst	*tmp;

	tmp = list;
	while (tmp)
	{
		printf("token = %s & token type = %d\n", tmp->token, tmp->token_type);
		tmp = tmp->next;
	}
}
