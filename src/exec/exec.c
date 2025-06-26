/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diavolo <diavolo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:03:20 by diavolo           #+#    #+#             */
/*   Updated: 2023/11/04 18:50:19 by diavolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*make_env_two(t_mini *mini_env, char **env)
{
	t_mini	*tmp;
	int		i;

	i = 0;
	tmp = mini_env;
	while (tmp)
	{
		env[i] = malloc(sizeof(char) * (ft_strlen(tmp->var) + 1));
		if (!env[i])
			return (ft_free_tabx2(env), NULL);
		i++;
		tmp = tmp->next;
	}
	return (NULL);
}

char	**make_env(t_mini *mini_env)
{
	char	**env;
	t_mini	*tmp;
	int		i;

	i = 0;
	tmp = mini_env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	make_env_two(mini_env, env);
	tmp = mini_env;
	i = 0;
	while (tmp)
	{
		ft_strncpy(env[i], tmp->var, (ft_strlen(tmp->var) + 1));
		i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}

void	one_pipe(t_cmds *data_exec, t_data *data)
{
	pid_t	pid;
	int		stat;

	stat = 0;
	pid = fork();
	if (pid == 0)
	{
		if (data_exec->cmd)
		{
			if ((ft_verif_space(data_exec->cmd) == 1))
				exec_one(data_exec, data, data_exec->infile,
					data_exec->outfile);
			else
				exec_two(data_exec, data, data_exec->infile,
					data_exec->outfile);
		}
	}
	waitpid(pid, &stat, 0);
	if (data_exec->outfile != 1 && data_exec->outfile != -1)
		close(data_exec->outfile);
	if (data_exec->infile != 0 && data_exec->infile != -1)
		close(data_exec->infile);
	unlink(".tmp_5546412sdfsdg46351g5fs646129");
	if (WIFEXITED(stat))
		g_exit_status = WEXITSTATUS(stat);
}

void	exec(t_cmds **data_exec, t_data *data, t_mini *mini_env)
{
	put_env(data_exec, data, mini_env);
	if (data->ncmd == 1)
	{
		if ((*data_exec)->path)
		{
			if ((*data_exec)->outfile != -1 && (*data_exec)->outfile != 1)
				exec_builtin(*data_exec, data, (*data_exec)->outfile, 2);
			else
				exec_builtin(*data_exec, data, (*data_exec)->infile, 2);
		}
		else
			one_pipe(*data_exec, data);
	}
	else
		xcution(data_exec, data);
}
