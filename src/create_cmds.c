/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:17:11 by thenry            #+#    #+#             */
/*   Updated: 2023/11/08 19:10:51 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmds	*full_words(t_cmds *cmd_list, t_second_lst *sl)
{
	t_second_lst	*tmp;
	int				i;

	i = 0;
	tmp = sl;
	while (tmp)
	{
		if (tmp->token_type == WORD)
		{
			if (!cmd_list[i].cmd)
				cmd_list[i].cmd = ft_strdup(tmp->token);
			else if (ft_strcmp(tmp->token, "") != 0)
			{
				cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd, " ");
				cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd, tmp->token);
			}
		}
		else if (tmp->token_type == SPIPE)
			i++;
		tmp = tmp->next;
	}
	return (cmd_list);
}

t_cmds	*handle_builtin(t_cmds *cmd_list, t_second_lst *sl, int i)
{
	char	**tab;

	while (i < count_cmd(sl))
	{
		tab = ft_split(cmd_list[i].cmd, ' ');
		if (!tab[0])
			return (ft_free_tabx2(tab), cmd_list);
		if (ft_strcmp(tab[0], "export") == 0)
			cmd_list[i].path = "{EXPORT BUILTIN}";
		else if (ft_strcmp(tab[0], "env") == 0)
			cmd_list[i].path = "{ENV BUILTIN}";
		else if (ft_strcmp(tab[0], "cd") == 0)
			cmd_list[i].path = "{CD BUILTIN}";
		else if (ft_strcmp(tab[0], "pwd") == 0)
			cmd_list[i].path = "{PWD BUILTIN}";
		else if (ft_strcmp(tab[0], "unset") == 0)
			cmd_list[i].path = "{UNSET BUILTIN}";
		else if (ft_strcmp(tab[0], "exit") == 0)
			cmd_list[i].path = "{EXIT BUILTIN}";
		else if (ft_strcmp(tab[0], "echo") == 0)
			cmd_list[i].path = "{ECHO BUILTIN}";
		ft_free_tabx2(tab);
		i++;
	}
	return (cmd_list);
}

t_cmds	*find_cmds(t_cmds *cmd_list, t_second_lst *sl)
{
	int	i;

	i = 0;
	cmd_list = find_infile(cmd_list, sl);
	cmd_list = find_heredoc(cmd_list, sl);
	if (!cmd_list)
		return (NULL);
	cmd_list = find_outfile(cmd_list, sl);
	cmd_list = full_words(cmd_list, sl);
	cmd_list = check_null_cmd(cmd_list, sl);
	if (!cmd_list)
		return (NULL);
	cmd_list = handle_builtin(cmd_list, sl, i);
	return (cmd_list);
}

/*
t_cmds	*find_cmds(t_cmds *cmd_list, t_second_lst *sl)
{
	t_second_lst	*tmp;
	int				i;

	tmp = sl;
	i = 0;
	while (tmp)
	{
		if (tmp->token_type == LESS && tmp->next
			&& tmp->next->token_type == WORD)
		{
			cmd_list[i].infile = open(tmp->next->token, O_RDONLY);
			tmp = tmp->next->next;
		}
		else if (tmp->token_type == DLESS && tmp->next
			&& tmp->next->token_type == WORD)
		{
			cmd_list[i].infile = INT_MAX;
			here_doc(&cmd_list[i], tmp->next->token);
			tmp = tmp->next->next;
		}
		else if (tmp->token_type == DLESS && (!tmp->next
				|| tmp->next->token_type != WORD))
		{
			ft_error("minishell: error: heredoc limiter missing\n");
			return (NULL);
		}
		else if (tmp->token_type == GREAT && tmp->next
			&& tmp->next->token_type == WORD)
		{
			cmd_list[i].outfile = open(tmp->next->token,
					O_CREAT | O_WRONLY | O_TRUNC, 0777);
			tmp = tmp->next->next;
		}
		else if (tmp->token_type == DGREAT && tmp->next
			&& tmp->next->token_type == WORD)
		{
			cmd_list[i].outfile = open(tmp->next->token,
					O_CREAT | O_WRONLY | O_APPEND, 0777);
			tmp = tmp->next->next;
		}
		else if (ft_strcmp(tmp->token, "export") == 0 && tmp->next
			&& tmp->next->token_type == WORD)
		{
			if (!cmd_list[i].cmd)
			{
				cmd_list[i].cmd = ft_strdup(tmp->token);
				while (tmp->next)
				{
					if (ft_strchr(tmp->next->token, '='))
						break ;
					else
						tmp = tmp->next;
				}
				if (tmp->next)
				{
					cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd, " ");
					cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd,
							tmp->next->token);
				}
				cmd_list[i].path = "{EXPORT BUILTIN}";
				while (tmp && tmp->token_type != SPIPE)
				{
					tmp = tmp->next;
				}
			}
			else
			{
				cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd, " ");
				cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd, tmp->token);
				tmp = tmp->next;
			}
		}
		else if (ft_strcmp(tmp->token, "export") == 0 && (!tmp->next
				|| tmp->next->token_type == SPIPE))
		{
			if (!cmd_list[i].cmd)
			{
				cmd_list[i].cmd = ft_strdup(tmp->token);
				cmd_list[i].path = "{EXPORT BUILTIN}";
				tmp = tmp->next;
			}
		}
		else if (ft_strcmp(tmp->token, "exit") == 0 && tmp->next
			&& tmp->next->token_type == WORD)
		{
			if (!cmd_list[i].cmd)
			{
				cmd_list[i].cmd = ft_strdup(tmp->token);
				cmd_list[i].path = "{EXIT BUILTIN}";
				tmp = tmp->next;
			}
			else
			{
				cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd, " ");
				cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd, tmp->token);
				tmp = tmp->next;
			}
		}
		else if (ft_strcmp(tmp->token, "exit") == 0 && (!tmp->next
				|| tmp->next->token_type == SPIPE))
		{
			if (!cmd_list[i].cmd)
			{
				cmd_list[i].cmd = ft_strdup(tmp->token);
				cmd_list[i].path = "{EXIT BUILTIN}";
				tmp = tmp->next;
			}
		}
		else if (ft_strcmp(tmp->token, "pwd") == 0)
		{
			if (!cmd_list[i].cmd)
			{
				cmd_list[i].cmd = ft_strdup(tmp->token);
				cmd_list[i].path = "{PWD BUILTIN}";
				while (tmp && tmp->token_type != SPIPE)
					tmp = tmp->next;
			}
			else
			{
				cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd, " ");
				cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd, tmp->token);
				tmp = tmp->next;
			}
		}
		else if (ft_strcmp(tmp->token, "unset") == 0 && tmp->next
			&& tmp->next->token_type == WORD)
		{
			if (!cmd_list[i].cmd)
			{
				cmd_list[i].cmd = ft_strdup(tmp->token);
				if (tmp->next)
				{
					cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd, " ");
					cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd,
							tmp->next->token);
				}
				cmd_list[i].path = "{UNSET BUILTIN}";
				while (tmp && tmp->token_type != SPIPE)
				{
					tmp = tmp->next;
				}
			}
			else
			{
				cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd, " ");
				cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd, tmp->token);
				tmp = tmp->next;
			}
		}
		else if (ft_strcmp(tmp->token, "unset") == 0 && (!tmp->next
				|| tmp->next->token_type == SPIPE))
		{
			if (!cmd_list[i].cmd)
			{
				cmd_list[i].cmd = ft_strdup(tmp->token);
				cmd_list[i].path = "{UNSET BUILTIN}";
				tmp = tmp->next;
			}
			else
			{
				cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd, " ");
				cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd, tmp->token);
				tmp = tmp->next;
			}
		}
		else if (ft_strcmp(tmp->token, "env") == 0 && (!tmp->next
				|| tmp->next->token_type == SPIPE))
		{
			if (!cmd_list[i].cmd)
			{
				cmd_list[i].cmd = ft_strdup(tmp->token);
				cmd_list[i].path = "{ENV BUILTIN}";
				tmp = tmp->next;
			}
			else
			{
				cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd, " ");
				cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd, tmp->token);
				tmp = tmp->next;
			}
		}
		else if (ft_strcmp(tmp->token, "env") == 0 && tmp->next
			&& tmp->next->token_type == WORD)
		{
			if (!cmd_list[i].cmd)
			{
				cmd_list[i].cmd = ft_strdup(tmp->token);
				if (tmp->next)
				{
					cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd, " ");
					cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd,
							tmp->next->token);
				}
				cmd_list[i].path = "{ENV BUILTIN}";
				while (tmp && tmp->token_type != SPIPE)
				{
					tmp = tmp->next;
				}
			}
			else
			{
				cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd, " ");
				cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd, tmp->token);
				tmp = tmp->next;
			}
		}
		else if (ft_strcmp(tmp->token, "echo") == 0)
		{
			if (!cmd_list[i].cmd)
			{
				cmd_list[i].cmd = ft_strdup(tmp->token);
				cmd_list[i].path = "{ECHO BUILTIN}";
				tmp = tmp->next;
			}
			else
			{
				cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd, " ");
				cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd, tmp->token);
				tmp = tmp->next;
			}
		}
		else if (ft_strcmp(tmp->token, "cd") == 0)
		{
			if (!cmd_list[i].cmd)
			{
				cmd_list[i].cmd = ft_strdup(tmp->token);
				cmd_list[i].path = "{CD BUILTIN}";
				tmp = tmp->next;
			}
			else
			{
				cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd, " ");
				cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd, tmp->token);
				tmp = tmp->next;
			}
		}
		else if (tmp->token_type == WORD)
		{
			if (!cmd_list[i].cmd)
				cmd_list[i].cmd = ft_strdup(tmp->token);
			else
			{
				cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd, " ");
				cmd_list[i].cmd = ft_join_and_free(cmd_list[i].cmd, tmp->token);
			}
			tmp = tmp->next;
		}
		else if (tmp->token_type == SPIPE)
		{
			i++;
			tmp = tmp->next;
		}
	}
	return (cmd_list);
}
*/

t_cmds	*last_check(t_cmds *cmd_list, int nbc)
{
	int		i;
	t_cmds	*tmp;

	tmp = cmd_list;
	i = 0;
	while (i < nbc)
	{
		if (!tmp[i].cmd && tmp[i].infile == 1)
		{
			ft_error("minishell: parse error\n");
			g_exit_status = 130;
			ft_lst_clear_cmds(&cmd_list, nbc);
			return (NULL);
		}
		else if (ft_strcmp(tmp[i].cmd, "") == 0)
		{
			unlink(".tmp_5546412sdfsdg46351g5fs646129");
			g_exit_status = 130;
			ft_lst_clear_cmds(&cmd_list, nbc);
			return (NULL);
		}
		i++;
	}
	return (cmd_list);
}

t_cmds	*create_cmds(t_second_lst *sl)
{
	int		nbc;
	t_cmds	*cmd_list;

	nbc = count_cmd(sl);
	cmd_list = malloc(sizeof(t_cmds) * nbc);
	if (!cmd_list)
	{
		ft_error("Error: malloc cmds\n");
		return (NULL);
	}
	if (init_cmds(cmd_list, nbc) == -1)
	{
		ft_error("Error: init cmds\n");
		return (NULL);
	}
	cmd_list = find_cmds(cmd_list, sl);
	if (!cmd_list)
		return (NULL);
	cmd_list = last_check(cmd_list, nbc);
	if (!cmd_list)
		return (NULL);
	return (cmd_list);
}
