/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diavolo <diavolo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:24:33 by diavolo           #+#    #+#             */
/*   Updated: 2023/11/02 20:05:00 by diavolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_find_bin(char **tab, int i, int o)
{
	char	*str;

	str = NULL;
	while (tab[i])
	{
		o = access(tab[i], F_OK | X_OK);
		if (o == 0)
		{
			o = ft_strlen(tab[i]);
			str = malloc(sizeof(char) * (o + 1));
			ft_strlcpy(str, tab[i], (o + 1));
			return (str);
		}
		i++;
	}
	return (NULL);
}

char	*ft_cut_path(char *path)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		path++;
		i++;
	}
	return (path);
}

char	*ft_path(char *path, t_mini *mini_env)
{
	t_mini	*tmp;

	tmp = mini_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "PATH=", 5) == 0)
		{
			path = tmp->var;
			return (path);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ft_path_bin(char *cmd, t_mini *mini_env)
{
	int		i;
	int		o;
	char	**tab;
	char	*path;

	path = NULL;
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	path = ft_path(path, mini_env);
	if (path == NULL)
		return (NULL);
	i = 0;
	path = ft_cut_path(path);
	tab = ft_split_dos(path, ':', cmd);
	if (tab == NULL)
		return (NULL);
	o = 0;
	path = ft_find_bin(tab, i, o);
	ft_free_tabx2(tab);
	if (path == NULL)
		return (NULL);
	return (path);
}
