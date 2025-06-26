/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_sl_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:10:54 by thenry            #+#    #+#             */
/*   Updated: 2023/11/08 20:09:04 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_single_quotes(char *token, int i, int j)
{
	char	*cpy;

	cpy = ft_strdup(token);
	if (!cpy)
		return (NULL);
	while (cpy[i])
	{
		if (cpy[i] == '\'')
		{
			i++;
			while (cpy[i] && cpy[i] != '\'')
				token[j++] = cpy[i++];
			i++;
			continue ;
		}
		token[j] = cpy[i];
		if (cpy[i])
			i++;
		j++;
	}
	token[j] = '\0';
	return (free(cpy), token);
}

char	*remove_double_quotes(char *token, int i, int j)
{
	char	*cpy;

	cpy = ft_strdup(token);
	if (!cpy)
		return (NULL);
	while (cpy[i])
	{
		if (cpy[i] == '\"')
		{
			i++;
			while (cpy[i] && cpy[i] != '\"')
				token[j++] = cpy[i++];
			i++;
			continue ;
		}
		token[j] = cpy[i];
		if (cpy[i])
			i++;
		j++;
	}
	token[j] = '\0';
	return (free(cpy), token);
}

int	ft_in_quotes(char *token)
{
	int	i;

	i = 0;
	if (!token)
		return (0);
	while (token[i] && (token[i] != '\'' || token[i] != '\"'))
		i++;
	if (token[i] == '\0')
		return (0);
	i++;
	while (token[i])
		i++;
	i--;
	if (token[i] == '\'' || token[i] == '\"')
		return (1);
	return (0);
}

t_second_lst	*remove_outer_quotes(t_second_lst *second_list)
{
	t_second_lst	*tmp;

	tmp = second_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->token, "export") == 0 && tmp->next)
		{
			tmp = tmp->next->next;
			continue ;
		}
		else if (ft_strcmp(tmp->token, "echo") == 0 && tmp->next)
		{
			while (tmp && tmp->token_type == WORD)
				tmp = tmp->next;
			continue ;
		}
		else if (tmp->token_type == WORD)
		{
			tmp->token = remove_single_quotes(tmp->token, 0, 0);
			tmp->token = remove_double_quotes(tmp->token, 0, 0);
		}
		tmp = tmp->next;
	}
	return (second_list);
}
