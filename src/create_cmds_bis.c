/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmds_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 00:32:59 by thenry            #+#    #+#             */
/*   Updated: 2023/11/08 19:10:34 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd(t_second_lst *sl)
{
	int				i;
	t_second_lst	*tmp;

	i = 1;
	tmp = sl;
	while (tmp)
	{
		if (tmp->token_type == SPIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	init_cmds(t_cmds *cmd_list, int nbc)
{
	int	i;

	i = 0;
	(void)cmd_list;
	while (i < nbc)
	{
		cmd_list[i].cmd = NULL;
		cmd_list[i].path = NULL;
		cmd_list[i].infile = STDIN_FILENO;
		cmd_list[i].outfile = STDOUT_FILENO;
		i++;
	}
	return (0);
}

t_cmds	*find_infile(t_cmds *cmd_list, t_second_lst *sl)
{
	t_second_lst	*tmp;
	int				i;

	i = 0;
	tmp = sl;
	while (tmp)
	{
		if (tmp->token_type == LESS && tmp->next
			&& tmp->next->token_type == WORD)
		{
			cmd_list[i].infile = open(tmp->next->token, O_RDONLY);
			free(tmp->next->token);
			tmp->next->token = ft_strdup("");
			tmp = tmp->next;
		}
		else if (tmp->token_type == SPIPE)
			i++;
		tmp = tmp->next;
	}
	return (cmd_list);
}

t_cmds	*find_heredoc(t_cmds *cmd_list, t_second_lst *sl)
{
	t_second_lst	*tmp;
	int				i;

	i = 0;
	tmp = sl;
	while (tmp)
	{
		if (tmp->token_type == DLESS && tmp->next
			&& tmp->next->token_type == WORD)
		{
			cmd_list[i].infile = INT_MAX;
			here_doc(&cmd_list[i], tmp->next->token);
			free(tmp->next->token);
			tmp->next->token = ft_strdup("");
			tmp = tmp->next;
		}
		else if (tmp->token_type == DLESS && (!tmp->next
				|| tmp->next->token_type != WORD))
			return (ft_error("minishell: error: heredoc limiter\n"), NULL);
		else if (tmp->token_type == SPIPE)
			i++;
		tmp = tmp->next;
	}
	return (cmd_list);
}

t_cmds	*find_outfile(t_cmds *cmd_list, t_second_lst *sl)
{
	t_second_lst	*tmp;
	int				i;

	i = 0;
	tmp = sl;
	while (tmp)
	{
		if ((tmp->token_type == GREAT || tmp->token_type == DGREAT) && tmp->next
			&& tmp->next->token_type == WORD)
		{
			if (tmp->token_type == GREAT)
				cmd_list[i].outfile = open(tmp->next->token,
						O_CREAT | O_WRONLY | O_TRUNC, 0777);
			else
				cmd_list[i].outfile = open(tmp->next->token,
						O_CREAT | O_WRONLY | O_APPEND, 0777);
			free(tmp->next->token);
			tmp->next->token = ft_strdup("");
			tmp = tmp->next;
		}
		else if (tmp->token_type == SPIPE)
			i++;
		tmp = tmp->next;
	}
	return (cmd_list);
}
