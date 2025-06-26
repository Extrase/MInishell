/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:39:49 by thenry            #+#    #+#             */
/*   Updated: 2023/11/08 20:05:18 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_no_quotes(char *token, t_mini *mini_env)
{
	int		i;
	char	*cpy;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && token[i + 1]
			&& token[i + 1] != ' ' && token[i + 1] != '$')
		{
			cpy = full_expanded_token(token, mini_env, &i);
			free(token);
			token = ft_strdup(cpy);
			free(cpy);
			i = 0;
			continue ;
		}
		i++;
	}
	return (token);
}

char	*ft_quotes_ter(char *cpy, char *token, t_mini *mini_env, int *i)
{
	cpy = full_expanded_token(token, mini_env, i);
	free(token);
	token = ft_strdup(cpy);
	free(cpy);
	(*i) = 0;
	return (token);
}

void	iterate_singleq(char *token, int *i)
{
	if (token[*i] == '\'')
	{
		(*i)++;
		while (token[*i] && token[*i] != '\'')
			(*i)++;
	}
}

char	*ft_quotes_bis(char *token, t_mini *mini_env, int i, char *cpy)
{
	int	flag;

	while (token[i])
	{
		iterate_singleq(token, &i);
		if (token[i] == '\"')
		{
			flag = ++i;
			while (token[i] && token[i] != '\"')
			{
				if (condition(token, i))
				{
						token = ft_quotes_ter(cpy, token, mini_env, &i);
						i = flag;
				}
				else if (token[i] == '$')
					dollar_iteration(token, &i);
				else
					i++;
			}
		}
		if (token[i])
			i++;
	}
	return (token);
}

char	*ft_quotes(char *token, t_mini *mini_env)
{
	int		i;
	char	*cpy;

	i = 0;
	cpy = NULL;
	if (ft_unclosed_singleq(token))
		return (free(token), NULL);
	if (ft_unclosed_doubleq(token))
		return (free(token), NULL);
	if (!ft_strchr(token, '\'') && !ft_strchr(token, '\"'))
	{
		token = ft_no_quotes(token, mini_env);
		return (token);
	}
	return (ft_quotes_bis(token, mini_env, i, cpy));
}
