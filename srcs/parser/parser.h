/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:42:50 by kallard           #+#    #+#             */
/*   Updated: 2020/11/11 10:52:37 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_PARSER_H
# define FT_MINISHELL_PARSER_H

# include "../minishell.h"

typedef enum	e_commands_index
{
	COMMAND_EXTERNAL = 0,
	COMMAND_CD,
	COMMAND_ECHO,
	COMMAND_EXPORT,
	COMMAND_EXIT,
	COMMAND_ENV,
	COMMAND_PWD,
	COMMAND_UNSET,
	NONE_COMMAND
}				t_command;

typedef struct	s_redirects
{
	int			stdout_fd;
	int			stdout_original;
	int			stdin_fd;
	int			stdin_original;
}				t_redirects;

int				t_redirects_close(t_redirects *redirects);
int				is_block(t_lexema *lexema);

t_list_lexema	*get_lexema_list(char *commandline, int *res);
void			parser_debug_print_lexema_list(t_list_lexema *lexema_list);
void			parser_debug_print_envs_list(t_list_env *lexema_list);

char			*get_var_name(char *str);
void			str_join_str(char **str1, char *str2);
void			str_join_char(char **str1, char ch);

void			eval_var(char **str_eval, char **str_original, \
				t_list_env *envs);
void			eval_param(char **str_eval, char **str_original, \
				int argc, char **argv);
void			eval_last_exit_value(char **str_eval, char **str_original);
void			eval_tilda(char **str_eval, char **str_original, \
				t_list_env	*envs);

int				check_marker_syntaxis(t_list_lexema *lexema_list);
t_list_lexema	*get_next_lexema_chain(t_list_lexema **lexema_list,\
				t_lexema_type delimeter);
void			eval_vars_unesc_dol_in_lex_chain(t_list_lexema *lexema_chain, \
				t_args_struct *args_struct);
void			join_lexemas_without_spaces(t_list_lexema *lexema_chain);
void			remove_empty_elements(t_list_lexema **lexema_chain);

int				is_var_name_symbol(char symbol);
int				is_var_name_symbol_with_num(char symbol);

int				parser(char *commandline, t_args_struct	*args_struct);
int				eval_with_pipe_or_without(t_list_lexema *lexema_chain, \
				t_list_env *envs);
int				eval_with_pipe(t_list_lexema *lexema_chain, t_list_env *envs);
int				eval_without_pipe(t_list_lexema *lexema_chain, \
				t_list_env *envs);
void			unexpected_error_exit(int exit_flag);
int				is_pipe_in_lexema_chain(t_list_lexema *lexema_chain);
int				eval_with_redirect_or_without(t_list_lexema \
				*one_command_lexemas, t_list_env *envs);
int				eval_with_fork_or_without(t_list_lexema *one_command_lexemas, \
				t_list_env *envs);
int				exec_external_or_builtin_command(t_list_lexema *lexema_chain, \
				t_list_env *envs);
int				external_command_exist(char	*command_name, \
t_list_lexema	*lexema_chain, t_list_env *envs);
char			**lexema_chain_2_argv(t_list_lexema *lexema_chain);
char			**list_env_2_env(t_list_env *env_list);

t_command		get_command_type(char *command_name);

/*
** PARSER_LEXEMA (2 and 3)
*/

int				malloc_error(char *commandline);
int				read_quote_param(char **commandline, t_lexema *lexema, \
				char quote_char);
int				read_pipe(char **commandline, t_lexema *lexema);
int				read_semicolon(char **commandline, t_lexema *lexema);
int				read_redirect_to(char **commandline, t_lexema *lexema);

int				is_blank(char symbol);
int				skip_blank(char**commandline);
void			read_simple_symbol(char **commandline, t_lexema *lexema);
int				read_escape(char **commandline, t_lexema *lexema, \
				int is_var_support);
int				error_end_of_line(char quote_char);

/*
**EVAL_WITH_REDIRECT_OR_WITHOUT (2 and 3)
*/

int				is_redirect(t_lexema *lexema);
int				is_redirect_exist(t_list_lexema *lexemas);
t_list_lexema	*get_next_redirect(t_list_lexema **redirect, int *res);
int				open_redirect_fd(int *current_fd, int std_fd, \
				char *filename, int flags);
int				redir_stdin(t_redirects *redirects_fd, char *filename, \
				int flags);
int				redir_stdout(t_redirects *redirects_fd, char *filename, \
				int flags);

#endif
