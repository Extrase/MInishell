/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_sl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:37:36 by thenry            #+#    #+#             */
/*   Updated: 2023/11/08 19:15:55 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_second_lst	*clean_quotes_and_expand(t_second_lst *second_list,
		t_mini *mini_env)
{
	t_second_lst	*tmp;

	tmp = second_list;
	while (tmp)
	{
		tmp->token = ft_quotes(tmp->token, mini_env);
		if (!tmp->token)
		{
			ft_lst_clear_sl(&second_list);
			return (NULL);
		}
		tmp = tmp->next;
	}
	return (second_list);
}

t_second_lst	*determine_token_type(t_second_lst *second_list)
{
	t_second_lst	*tmp;

	tmp = second_list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->token, ">>"))
			tmp->token_type = DGREAT;
		else if (!ft_strcmp(tmp->token, "<<"))
			tmp->token_type = DLESS;
		else if (!ft_strcmp(tmp->token, ">"))
			tmp->token_type = GREAT;
		else if (!ft_strcmp(tmp->token, "<"))
			tmp->token_type = LESS;
		else if (!ft_strcmp(tmp->token, "|"))
			tmp->token_type = SPIPE;
		else if (ft_crap_operator(tmp->token))
			return (ft_lst_clear_sl(&second_list),
				ft_error("minishell: parsing error crap op\n"), NULL);
		else if (ft_in_quotes(tmp->token) == 0)
			tmp->token_type = WORD;
		else
			tmp->token_type = WORD;
		tmp = tmp->next;
	}
	return (second_list);
}

t_second_lst	*check_pipe(t_second_lst *second_list)
{
	t_second_lst	*tmp;

	tmp = second_list;
	if (tmp->token_type == SPIPE)
	{
		g_exit_status = 1;
		ft_lst_clear_sl(&second_list);
		ft_error("minishell: error: pipe at the beginning\n");
		return (NULL);
	}
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->token_type == SPIPE)
	{
		g_exit_status = 1;
		ft_lst_clear_sl(&second_list);
		ft_error("minishell: error: pipe at the end\n");
		return (NULL);
	}
	return (second_list);
}

t_second_lst	*clean_second_list(t_second_lst *second_list, t_mini *mini_env)
{
	if (!second_list)
		return (NULL);
	second_list = clean_quotes_and_expand(second_list, mini_env);
	if (!second_list)
		return (NULL);
	second_list = determine_token_type(second_list);
	if (!second_list)
		return (NULL);
	second_list = remove_outer_quotes(second_list);
	second_list = check_pipe(second_list);
	if (!second_list)
		return (NULL);
	return (second_list);
}

int	ft_crap_operator(char *token)
{
	if (ft_strchr(token, '\'') || ft_strchr(token, '\"'))
		return (0);
	if (ft_strchr(token, '>') && (ft_strcmp(token, ">") || ft_strcmp(token,
				">>")))
	{
		g_exit_status = 2;
		return (1);
	}
	else if (ft_strchr(token, '<') && (ft_strcmp(token, "<") || ft_strcmp(token,
				"<<")))
	{
		g_exit_status = 2;
		return (1);
	}
	else if (ft_strchr(token, '|') && ft_strcmp(token, "|"))
	{
		g_exit_status = 2;
		return (1);
	}
	return (0);
}
