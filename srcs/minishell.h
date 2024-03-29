/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:38:29 by kallard           #+#    #+#             */
/*   Updated: 2020/11/11 11:12:00 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>

# include <dirent.h>

# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct				s_env
{
	char					*key;
	char					*value;
}							t_env;

typedef	struct				s_list_env
{
	t_env					*env;
	struct s_list_env		*next;
}							t_list_env;

typedef struct				s_args_struct
{
	int						argc;
	char					**argv;
	t_list_env				*envs;
}							t_args_struct;

int							g_exit_value;

typedef enum				e_lexema_type
{
	lexema_type_default = 0,
	lexema_type_simple_word,
	lexema_type_double_q,
	lexema_type_single_q,
	lexema_type_semicolon,
	lexema_type_redirect_to_append,
	lexema_type_redirect_to,
	lexema_type_redirect_from,
	lexema_type_pipe
}							t_lexema_type;

typedef struct				s_lexema
{
	char					*string;
	int						has_space_before;
	t_lexema_type			lexema_type;
}							t_lexema;

typedef struct				s_all
{
	int						argc;
	t_list					*envs;
}							t_all;

typedef	struct				s_list_lexema
{
	t_lexema				*lexema;
	struct s_list_lexema	*next;
}							t_list_lexema;

typedef struct				s_pipe
{
	char					*left_end;
	char					**argv;
}							t_pipe;

enum						e_quotes
{
	SING_Q = 0,
	DUBL_Q,
	ETC
};

typedef	struct				s_quotes
{
	int						type;
	int						start;
	int						end;
}							t_quotes;

t_lexema					*t_lexema_init();
t_lexema					*t_lexema_copy(t_lexema *original);
int							lexema_chain_free(t_list_lexema *lexema_chain);
t_list_lexema				*lexema_chain_copy(t_list_lexema *lexema_chain);

t_list						*get_envs(char **envp);
void						write_prompt();

int							deal_with_input(char **line);
char						**get_comands(char *line);
char						*find_path(char *argv, t_list *envs);
char						**get_argumentes(char *line, t_list *envs);
char						*deal_with_quotes(char *argv, t_list *envs);
char						*insert_variable(char *argv, t_list *envs);
int							print_exit_status(char *line);
void						execute_commands(char *line, t_list *envs);

void						execute_pipes(char *line, t_list *envs);
void						execute_others(char *line, t_list *envs);
int							execute_builtins(char *line, t_list *envs);
int							command_cd(char **argv, t_list *envs);
int							command_echo(char **argv);
int							command_pwd(t_list_env *envs);
int							command_env(t_list *envs);
int							command_export(char **argv, t_list_env *envs);
int							command_unset(char **argv, t_list *envs, int i);
int							command_exit(char **argv);

int							pipe_found(char *line);
int							redirect_found(char *line);
int							dollar_found(char *line);
int							quote_found(char *line);

char						*get_env_value(char *key, t_list_env *envs);
int							is_this_key_env(char *key, t_list_env *envs);
int							is_redirect(t_lexema *lexema);

int							update_env_data(t_list_env *envs, char *new_env,\
							char *new_data);

void						free_double_array(char **array);
int							error_no_cmd(char *cmd);
int							error_no_file_dir(char *cmd);
int							valid_name_first(int ch);
int							valid_name(char *str);
int							count_argv(char **argv);
void						free_envs_list(t_list_env *envs);

void						signals();

#endif
