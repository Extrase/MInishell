/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:28:03 by thenry            #+#    #+#             */
/*   Updated: 2023/11/08 18:48:34 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <limits.h> // INT_MAX
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>

extern int				g_exit_status;

// lower case letter
// UPPER CASE LETTER
// numeric
// space character ' '
// tab character "	" (\t)
// '\n'
// -
// ;
// ''
// ""
// (
// )
// &
// $
// |
// < (redirect the input)
// > (it does redirect the output)
// escape character '\'
// '\0'
// other char / wrong char

enum					e_char_type
{
	LALPHA,
	UALPHA,
	NUM,
	FTSPACE,
	FTTAB,
	FTNEWLINE,
	DASH,
	SEMICOL,
	SQUOTE,
	DQUOTE,
	OPARENT,
	CPARENT,
	AMPERSAND,
	DOLLAR,
	PIPE,
	REDIRIN,
	REDIROUT,
	ESCAPE,
	EOL,
	OTHER
};

enum					e_token_type
{
	WORD,
	LESS,
	DLESS,
	GREAT,
	DGREAT,
	SPIPE
};

typedef struct s_first_lst
{
	char				c;
	char				cs[2];
	int					type;
	struct s_first_lst	*next;
}						t_first_lst;

typedef struct s_second_lst
{
	char				*token;
	int					token_type;
	struct s_second_lst	*next;
}						t_second_lst;

typedef struct s_mini
{
	char				*var;
	struct s_mini		*next;
}						t_mini;

typedef struct s_data
{
	int					**pipe;
	int					ncmd;
	t_first_lst			*first_list;
	t_second_lst		*second_list;
	char				*prompt;
	t_mini				*mini_env;
	struct s_cmds		*cmd_list;
}						t_data;

typedef struct s_cmds
{
	char				*cmd;
	char				*path;
	int					infile;
	int					outfile;
	t_data				*data;
	t_mini				*mini_env;
}						t_cmds;

typedef struct s_parse
{
	char				*prompt;
	t_mini				*mini_env;
	t_first_lst			*first_list;
	t_second_lst		*second_list;
	t_cmds				*cmd_list;
}						t_parse;

// cd_builtin_bis.c

int						cd_old(t_mini **mini_env, int fd);
int						cd_home(t_mini **mini_env, int fd);
int						cd_path(t_mini **mini_env, char *path, int fd);

// cd_builtin.c

char					*get_env(t_mini **mini_env, char *var);
int						switch_dir(t_mini **mini_env, char *old, char *pwd,
							int fd);
int						cd_builtin(t_mini **mini_env, char **cmds, int fd);

// clean_sl.c

t_second_lst			*clean_quotes_and_expand(t_second_lst *second_list,
							t_mini *mini_env);
t_second_lst			*determine_token_type(t_second_lst *second_list);
t_second_lst			*check_pipe(t_second_lst *second_list);
t_second_lst			*clean_second_list(t_second_lst *second_list,
							t_mini *mini_env);
int						ft_crap_operator(char *token);

// cleal_sl_utils.c

char					*remove_single_quotes(char *token, int i, int j);
char					*remove_double_quotes(char *token, int i, int j);
int						ft_in_quotes(char *token);
t_second_lst			*remove_outer_quotes(t_second_lst *second_list);

// create_cmds_bis.c

int						count_cmd(t_second_lst *sl);
int						init_cmds(t_cmds *cmd_list, int nbc);
t_cmds					*find_infile(t_cmds *cmd_list, t_second_lst *sl);
t_cmds					*find_heredoc(t_cmds *cmd_list, t_second_lst *sl);
t_cmds					*find_outfile(t_cmds *cmd_list, t_second_lst *sl);

// create_cmds.c

t_cmds					*full_words(t_cmds *cmd_list, t_second_lst *sl);
t_cmds					*handle_builtin(t_cmds *cmd_list, t_second_lst *sl,
							int i);
t_cmds					*find_cmds(t_cmds *cmd_list, t_second_lst *sl);
t_cmds					*last_check(t_cmds *cmd_list, int nbc);
t_cmds					*create_cmds(t_second_lst *sl);

// create_cmds_ter.c

t_cmds					*check_null_cmd(t_cmds *cmd_list, t_second_lst *sl);

// echo_builtin.c

char					*clean_echo(char *cmds);
int						echo_builtin(char *cmds, int fd);

// env_builtin.c

int						env_error(char *cmds);
int						env_builtin(t_mini **mini, char *cmds, int fd);

// error.c

int						ft_error(char *str);

// exit_builtin.c

int						is_numeric(char *str);
void					exit_gain(char **cmds, t_data *data, t_cmds *data_exec,
							int o);
void					exit_gain_two(char **cmds, t_data *data,
							t_cmds *data_exec, int o);
int						exit_builtin(char **cmds, t_data *data,
							t_cmds *data_exec, int o);

// expansion.c

char					*shift_var(char *ov);
char					*get_var_ter(int j, t_mini *mini_env, int *i,
							char *only_var);
char					*get_var_bis(char *var, t_mini *mini_env, int *i,
							char *only_var);
char					*get_var(char *var, t_mini *mini_env, int *i);
char					*full_expanded_token(char *token, t_mini *mini_env,
							int *i);

// export_builtin.c

void					simple_export(t_mini **mini_env, int fd);
char					*get_var_to_unset(char *str);
void					correct_export(t_mini **mini_env, char **tab,
							char *cmds);
void					only_export(t_mini **mini_env, char **tab);
int						export_builtin(t_mini **mini_env, char *cmds, int fd);

// free.c

void					ft_lst_clear_fl(t_first_lst **list);
void					ft_lst_clear_sl(t_second_lst **list);
void					ft_lst_clear_env(t_mini **list);
void					ft_lst_clear_cmds(t_cmds **list, int ncmds);
char					*ft_join_and_free(char *reserve, char *buff);

// get_env.c

t_mini					*get_mini_env(char **env);
void					print_env(t_mini *mini);
t_mini					*ft_mini_last(t_mini *a);
t_mini					*ft_mini_new(char *var);
void					ft_mini_add_back(t_mini **a, t_mini *new);

// handle_quotes_bis.c

int						count_char(char c, char *token);
int						ft_unclosed_singleq(char *token);
int						ft_unclosed_doubleq(char *token);

// handle_quotes.c

char					*ft_no_quotes(char *token, t_mini *mini_env);
char					*ft_quotes_ter(char *cpy, char *token, t_mini *mini_env,
							int *i);
void					iterate_singleq(char *token, int *i);
char					*ft_quotes_bis(char *token, t_mini *mini_env, int i,
							char *cpy);
char					*ft_quotes(char *token, t_mini *mini_env);

// handle_quotes_utils.c

int						condition(char *token, int i);
void					dollar_iteration(char *token, int *i);

// history.c

int						bool_history(char *prompt);

// main.c

void					init_data(t_data *data, t_parse *main_struct,
							char *prompt);
int						init_parse(t_parse *main_struct, char *prompt);
int						handle_history(char *prompt);
void					shell_routine(t_parse *main_struct, t_data *data,
							int ncmds);

// print_all.c

void					print_cmd_list(t_cmds *cmd_list, t_second_lst *sl);

// pwd_builtin.c

int						pwd_builtin(int fd);

// signal.c

void					handle(int signal);
void					init_signals(void);

// tokenise_fl.c

t_first_lst				*ft_lst_last(t_first_lst *a);
t_first_lst				*ft_lst_new(char character, int in_quotes);
void					ft_lst_add_back(t_first_lst **a, t_first_lst *new);
t_first_lst				*fill_list_tmp(char *prompt);
void					print_lst(t_first_lst *list);

// tokenise_fl_utils.c

int						get_type_bis(char c);
int						get_type(char c);
int						ft_space(char c);
int						ft_is_quotes(char c);
int						ft_is_sep(char c);

// tokenise_sl.c

char					*handle_special_type(t_first_lst **first_list,
							char *tok);
char					*handle_regular_type(t_first_lst **first_list,
							char *tok);
t_second_lst			*fill_second_list(t_first_lst *first_list);

// tokenise_sl_utils_bis.c

int						is_separator_type(int type);
int						is_special_type(int type);
int						is_separator_or_operator(int type, char c);

// tokenise_sl_utils.c

t_second_lst			*ft_second_lst_last(t_second_lst *a);
t_second_lst			*ft_second_lst_new(char *tok, int tok_type);
void					ft_second_lst_add_back(t_second_lst **a,
							t_second_lst *new);
int						ft_is_op(char c);
void					print_second_lst(t_second_lst *list);

// unset_builtin.c

void					delete_var(t_mini *mini_env, char *var);
int						unset_builtin(t_mini **mini_env, char *cmds);

// utils.c

int						ft_strcmp(const char *s1, const char *s2);
int						ft_iscaps(char c);
char					*ft_strncpy(char *dest, char *src, int n);
void					special_free(int kase, char *prompt, t_first_lst *fl,
							t_second_lst *sl);

// EXEC
int						xcution(t_cmds **cmd_list, t_data *data);
void					ft_close_all(t_cmds **data_exec, t_data *data);
char					*ft_path_bin(char *cmd, t_mini *mini_env);
char					**ft_split_dos(char *s, char c, char *exe);
void					ft_free_tabx2(char **str);
void					ft_free_int(t_data *data, t_cmds **data_exec, int o);
void					ft_first_pipe(t_cmds *data_exec, t_data *data);
void					ft_inter_pipe(t_cmds *data_exec, int i, t_data *data);
void					ft_last_pipe(t_cmds *data_exec, int i, t_data *data);
void					put_env(t_cmds **data_exec, t_data *data,
							t_mini *mini_env);
void					ft_close_fd(int *fd);
int						ft_verif_space(char *str);
void					ft_free_list(char **father);
char					*ft_strjoin_two(char const *s1, char const *s2);
void					exec(t_cmds **data_exec, t_data *data,
							t_mini *mini_env);
void					exec_one(t_cmds *data_exec, t_data *data, int read_pipe,
							int write_pipe);
void					exec_two(t_cmds *data_exec, t_data *data, int read_pipe,
							int write_pipe);
void					here_doc(t_cmds *data_exec, char *limiter);
void					exec_builtin(t_cmds *data_exec, t_data *data, int fd,
							int o);
char					**make_env(t_mini *mini_env);
void					gain_line(char *path, char **str, t_cmds *data_exec,
							t_data *data);
void					gain_first(t_cmds *data_exec, t_data *data);
void					gain_inter(t_cmds *data_exec, t_data *data, int i);
void					gain_inter_two(t_cmds *data_exec, t_data *data, int i);
void					gain_last(t_cmds *data_exec, t_data *data, int i);
void					clear_gain(t_data *data, int alacon);
void					ft_make_thing(t_cmds *data_exec, t_data *data,
							int read_pipe, int write_pipe);
void					ft_make_thing_two(t_cmds *data_exec, t_data *data,
							int read_pipe, int write_pipe);
int						here_gain(char *line, char *limiter, t_cmds *data_exec);
void					delimiter_error(char *limiter);
int						here_comp(const char *s1, const char *s2, size_t n);

#endif
