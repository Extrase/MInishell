/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmds_ter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:33:02 by thenry            #+#    #+#             */
/*   Updated: 2023/11/08 17:33:44 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmds	*check_null_cmd(t_cmds *cmd_list, t_second_lst *sl)
{
	t_cmds	*tmp;
	int		i;

	i = 0;
	tmp = cmd_list;
	while (i < count_cmd(sl))
	{
		if (!cmd_list[i].cmd)
		{
			ft_lst_clear_cmds(&cmd_list, count_cmd(sl));
			ft_error("minishell: error: parsing error\n");
			return (NULL);
		}
		i++;
	}
	return (cmd_list);
}
