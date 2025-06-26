/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:57:01 by thenry            #+#    #+#             */
/*   Updated: 2023/11/08 19:45:04 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

void	init_data(t_data *data, t_parse *main_struct, char *prompt)
{
	data->ncmd = count_cmd(main_struct->second_list);
	data->first_list = main_struct->first_list;
	data->second_list = main_struct->second_list;
	data->prompt = prompt;
	data->cmd_list = main_struct->cmd_list;
	data->mini_env = main_struct->mini_env;
}

int	init_parse(t_parse *main_struct, char *prompt)
{
	main_struct->first_list = fill_list_tmp(prompt);
	if (!main_struct->first_list)
	{
		special_free(1, prompt, main_struct->first_list, NULL);
		return (1);
	}
	main_struct->second_list = fill_second_list(main_struct->first_list);
	main_struct->second_list = clean_second_list(main_struct->second_list,
			main_struct->mini_env);
	if (!main_struct->second_list)
	{
		special_free(1, prompt, main_struct->first_list, NULL);
		return (1);
	}
	main_struct->cmd_list = create_cmds(main_struct->second_list);
	if (!main_struct->cmd_list)
	{
		special_free(2, prompt, main_struct->first_list,
			main_struct->second_list);
		return (1);
	}
	return (0);
}

int	handle_history(char *prompt)
{
	if (bool_history(prompt) == 1)
		add_history(prompt);
	else
	{
		free(prompt);
		return (1);
	}
	return (0);
}

void	shell_routine(t_parse *main_struct, t_data *data, int ncmds)
{
	while (1)
	{
		init_signals();
		main_struct->prompt = readline("minishell:~$ ");
		if (main_struct->prompt)
		{
			if (handle_history(main_struct->prompt))
				continue ;
			if (init_parse(main_struct, main_struct->prompt))
				continue ;
			ncmds = count_cmd(main_struct->second_list);
			init_data(data, main_struct, main_struct->prompt);
			exec(&main_struct->cmd_list, data, main_struct->mini_env);
			special_free(2, main_struct->prompt, main_struct->first_list,
				main_struct->second_list);
			ft_lst_clear_cmds(&main_struct->cmd_list, ncmds);
		}
		else if (!main_struct->prompt)
		{
			ft_lst_clear_env(&main_struct->mini_env);
			printf("exit\n");
			g_exit_status = 0;
			break ;
		}
	}	
}

int	main(int ac, char **av, char **env)
{
	t_data			data;
	t_parse			main_struct;
	int				ncmds;

	(void)av;
	ncmds = 0;
	g_exit_status = 0;
	if (ac > 1)
		return (ft_putstr_fd("minishell: error: too many args\n", 2), 1);
	main_struct.mini_env = get_mini_env(env);
	shell_routine(&main_struct, &data, ncmds);
	exit(g_exit_status);
}
