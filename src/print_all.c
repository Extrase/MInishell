/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:41:41 by thenry            #+#    #+#             */
/*   Updated: 2023/11/04 17:06:06 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_list(t_cmds *cmd_list, t_second_lst *sl)
{
	t_cmds	*tmp;
	int		i;

	tmp = cmd_list;
	i = 0;
	while (i < count_cmd(sl))
	{
		printf("COMMAND %d\n", i);
		printf("        full cmd: @%s@\n", tmp[i].cmd);
		printf("        full path: %s\n", tmp[i].path);
		printf("        infile: %d\n", tmp[i].infile);
		printf("        outfile: %d\n", tmp[i].outfile);
		printf("---------------------------------\n");
		i++;
	}
}
