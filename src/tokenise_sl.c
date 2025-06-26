/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_sl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:23:06 by thenry            #+#    #+#             */
/*   Updated: 2023/11/04 14:23:25 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_special_type(t_first_lst **first_list, char *tok)
{
	while ((*first_list)->next && !is_separator_type((*first_list)->next->type))
	{
		tok = ft_join_and_free(tok, (*first_list)->next->cs);
		(*first_list) = (*first_list)->next;
	}
	return (tok);
}

char	*handle_regular_type(t_first_lst **first_list, char *tok)
{
	while ((*first_list)->next
		&& !is_separator_or_operator((*first_list)->next->type,
			(*first_list)->next->c))
	{
		tok = ft_join_and_free(tok, (*first_list)->next->cs);
		(*first_list) = (*first_list)->next;
	}
	return (tok);
}

t_second_lst	*fill_second_list(t_first_lst *first_list)
{
	t_second_lst	*second_list;
	t_second_lst	*new;
	char			*tok;

	second_list = NULL;
	new = NULL;
	while (first_list)
	{
		while (ft_space(first_list->c) && first_list->next)
			first_list = first_list->next;
		if (ft_space(first_list->c) && !first_list->next)
			break ;
		tok = ft_strdup(first_list->cs);
		if (is_special_type(first_list->type))
			tok = handle_special_type(&first_list, tok);
		else
			tok = handle_regular_type(&first_list, tok);
		new = ft_second_lst_new(ft_strdup(tok), -42);
		free(tok);
		ft_second_lst_add_back(&second_list, new);
		first_list = first_list->next;
	}
	return (second_list);
}

//-----------------------------------------------------------------//

/*
t_second_lst	*fill_second_list(t_first_lst *first_list)
{
	t_second_lst	*second_list;
	t_second_lst	*new;
	char			*tok;

	
	second_list = NULL;
	new = NULL;
	while (first_list)
	{
		while (ft_space(first_list->c) && first_list->next)
			first_list = first_list->next;
		if (ft_space(first_list->c) && !first_list->next)
			break ;
		tok = ft_strdup(first_list->cs);
		if (first_list->type == SQUOTE || first_list->type == DQUOTE
			|| first_list->type == DOLLAR)
		{
			while (first_list->next && !(first_list->next->type == FTSPACE
					|| first_list->next->type == FTTAB))
			{
				tok = ft_join_and_free(tok, first_list->next->cs);
				first_list = first_list->next;
			}
		}
		else if (first_list->type == PIPE || first_list->type == REDIRIN
			|| first_list->type == REDIROUT)
		{
			while (first_list->next
				&& (first_list->type == first_list->next->type))
			{
				tok = ft_join_and_free(tok, first_list->next->cs);
				first_list = first_list->next;
			}
		}
		else
		{
			while (first_list->next && (first_list->next->type != FTSPACE
					&& first_list->next->type != FTTAB
					&& !ft_is_op(first_list->next->c)))
			{
				tok = ft_join_and_free(tok, first_list->next->cs);
				first_list = first_list->next;
			}
		}
		new = ft_second_lst_new(ft_strdup(tok), -42);
		free(tok);
		ft_second_lst_add_back(&second_list, new);
		first_list = first_list->next;
	}
	return (second_list);
}
*/
