/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exec2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diavolo <diavolo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:04:00 by diavolo           #+#    #+#             */
/*   Updated: 2023/10/19 16:24:22 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_list(char **father)
{
	int	i;

	i = 0;
	if (father)
	{
		if (father[i])
		{
			while (father[i])
			{
				free(father[i]);
				i++;
			}
		}
		free(father);
	}
	return ;
}

char	*ft_strjoin_two(char const *s1, char const *s2)
{
	size_t		i;
	size_t		j;
	char		*copy;

	i = ft_strlen(((char *)s1));
	j = ft_strlen(((char *)s2));
	copy = malloc(sizeof(*s1) * (i + j) + 2);
	if (!copy)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		copy[i] = ((char *)s1)[i];
		++i;
	}
	j = 0;
	copy[i++] = '/';
	while (s2[j] && s2[j + 1] != '-')
	{
		copy[i] = ((char *)s2)[j];
		++j;
		++i;
	}
	copy[i] = '\0';
	return (copy);
}
