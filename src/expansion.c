/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:42:01 by thenry            #+#    #+#             */
/*   Updated: 2023/11/05 17:30:59 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*shift_var(char *ov)
{
	int	i;

	i = 0;
	while (ov[i] && ov[i + 1])
	{
		ov[i] = ov[i + 1];
		i++;
	}
	ov[i] = '=';
	ov[++i] = '\0';
	return (ov);
}

char	*get_var_ter(int j, t_mini *mini_env, int *i, char *only_var)
{
	t_mini	*tmp;
	int		len;

	tmp = mini_env;
	len = 0;
	while (tmp)
	{
		if (ft_strncmp(only_var, tmp->var, ft_strlen(only_var)) == 0)
		{
			(*i) += j;
			len = ft_strlen(only_var);
			free(only_var);
			return (ft_strdup(tmp->var + len));
		}
		tmp = tmp->next;
	}
	(*i) += j;
	free(only_var);
	return (ft_strdup(""));
}

char	*get_var_bis(char *var, t_mini *mini_env, int *i, char *only_var)
{
	int	j;

	j = 1;
	while (var[j] && var[j] != ' ' && var[j] != '\t' && var[j] != '$'
		&& var[j] != '\"' && var[j] != '\'')
	{
		only_var[j] = var[j];
		j++;
	}
	only_var[j] = '\0';
	if (ft_strcmp(only_var, "$") == 0)
		return (only_var);
	only_var = shift_var(only_var);
	return (get_var_ter(j, mini_env, i, only_var));
}

char	*get_var(char *var, t_mini *mini_env, int *i)
{
	char	*only_var;
	char	*str;

	if (ft_strncmp(var, "$?", 2) == 0)
	{
		str = ft_itoa(g_exit_status);
		if (ft_strlen(str) <= 2)
			(*i) += 2;
		else
			(*i) += ft_strlen(str);
		return (str);
	}
	only_var = ft_strdup(var);
	if (!only_var)
		return (ft_strdup(""));
	return (get_var_bis(var, mini_env, i, only_var));
}

char	*full_expanded_token(char *token, t_mini *mini_env, int *i)
{
	int		j;
	char	*cpy;
	char	*gv;

	j = 0;
	cpy = (char *)malloc(sizeof(char) * (*i) + 1);
	if (!cpy)
		return (NULL);
	while (j < (*i))
	{
		cpy[j] = token[j];
		j++;
	}
	cpy[j] = '\0';
	gv = get_var(token + (*i), mini_env, &(*i));
	cpy = ft_join_and_free(cpy, gv);
	free(gv);
	cpy = ft_join_and_free(cpy, token + (*i));
	return (cpy);
}
