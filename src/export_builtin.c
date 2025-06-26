/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diavolo <diavolo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:08:06 by thenry            #+#    #+#             */
/*   Updated: 2023/11/08 17:49:58 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simple_export(t_mini **mini_env, int fd)
{
	int		j;
	t_mini	*tmp;

	j = 0;
	tmp = *mini_env;
	while (tmp)
	{
		j = 0;
		ft_putstr_fd("export ", fd);
		while (tmp->var[j] && tmp->var[j] != '=')
			ft_putchar_fd(tmp->var[j++], fd);
		if (tmp->var[j] == '\0')
		{
			ft_putstr_fd("\n", fd);
			tmp = tmp->next;
			continue ;
		}
		ft_putstr_fd("=\"", fd);
		j++;
		while (tmp->var[j])
			ft_putchar_fd(tmp->var[j++], fd);
		ft_putstr_fd("\"\n", fd);
		tmp = tmp->next;
	}
	g_exit_status = 0;
}

/*
void	correct_export(t_mini **mini_env, char *cmds, int len, char **tab)
{
	int		i;
	int		j;
	char	*var;
	t_mini	*new;

	new = NULL;
	j = 0;
	i = 7;
	len = len - i;
	var = (char *)malloc(sizeof(char) * len + 1);
	if (!var)
	{
		g_exit_status = 1;
		return ;
	}
	while (cmds[i])
		var[j++] = cmds[i++];
	var[j] = '\0';
	new = ft_mini_new(var);
	ft_mini_add_back(mini_env, new);
	free(var);
	g_exit_status = 0;
	return ;
}
*/

char	*get_var_to_unset(char	*str)
{
	char	*tu;
	int		i;

	i = 0;
	tu = ft_strdup(str);
	while (str[i] && str[i] != '=')
	{
		tu[i] = str[i];
		i++;
	}
	tu[i] = '\0';
	return (tu);
}

void	correct_export(t_mini **mini_env, char **tab, char *cmds)
{
	char	*var;
	char	*to_unset;
	char	*tu;
	t_mini	*new;

	new = NULL;
	if (ft_strchr(tab[1], '\'') || ft_strchr(tab[1], '\"'))
	{
		var = ft_strdup(cmds + 7);
		var = remove_single_quotes(var, 0, 0);
		var = remove_double_quotes(var, 0, 0);
	}
	else
		var = ft_strdup(tab[1]);
	to_unset = get_var_to_unset(tab[1]);
	tu = ft_strjoin("unset ", to_unset);
	unset_builtin(mini_env, tu);
	new = ft_mini_new(var);
	ft_mini_add_back(mini_env, new);
	free(var);
	free(to_unset);
	free(tu);
	g_exit_status = 0;
	return ;
}

/*
char	*clean_cmd(char *cmds)
{
	int	i;

	i = 0;
	while (ft_isalpha(cmds[i]))
		i++;
	if (cmds[i] == ' ')
		i++;
	else
		return (NULL);
	while (ft_isalpha(cmds[i]))
		i++;
	if (cmds[i] == '=')
		i++;
	else
		return (NULL);
	while (ft_isalpha(cmds[i]))
		i++;
	while (cmds[i])
	{
		cmds[i] = '\0';
		i++;
	}
	return (cmds);
}
*/

void	only_export(t_mini **mini_env, char **tab)
{
	char	*var;
	char	*tu;
	t_mini	*new;

	new = NULL;
	var = ft_strdup(tab[1]);
	tu = ft_strjoin("unset ", var);
	unset_builtin(mini_env, tu);
	new = ft_mini_new(var);
	ft_mini_add_back(mini_env, new);
	free(var);
	free(tu);
	g_exit_status = 0;
	return ;
}

int	export_builtin(t_mini **mini_env, char *cmds, int fd)
{
	char		**tab;

	if (!cmds)
	{
		g_exit_status = 0;
		return (g_exit_status);
	}
	tab = ft_split(cmds, ' ');
	if (ft_strncmp(cmds, "export", ft_strlen(cmds)) == 0)
		simple_export(mini_env, fd);
	else if (ft_strncmp(cmds, "export =", 8) == 0)
		g_exit_status = 0;
	else if ((ft_strcmp(tab[0], "export") == 0) && ft_strchr(tab[1], '='))
		correct_export(mini_env, tab, cmds);
	else if (ft_strcmp(tab[0], "export") == 0 && tab[1])
		only_export(mini_env, tab);
	ft_free_tabx2(tab);
	return (g_exit_status);
}
