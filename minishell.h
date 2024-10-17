/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:59:04 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/19 17:43:04 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_exe
{
	int				pid;
	int				pipe_fd[2];
	int				fd_in;
	int				fd_out;
	int				n_fork;
	int				stat_log;
}					t_exe;

typedef struct s_data
{
	char			*line;
	char			**tokens;
	char			***cmds;
	char			**original_envp;
	char			**tmp_envp;
	char			**safe_envp;
	pid_t			child_pid;
	int				n_pipe;
	struct s_exe	*exe;
	int				env_null;
	int				path_flag;
	int				path_must_be_hidden;
	int				is_exported_flag;
	int				code_error;
	int				eof_flag;
	int				home_flag;
	int				oldpwd_flag;
	int				skip_token_processing;
	int				redir_signal;
}					t_data;

extern int			g_signal;

void				sigint_parent2(int sig);
void				sigint_child3(int sig);
void				sigint_parent3(int sig);

/* UTILS */

/* free_and_clean.c */

void				free_double_pointer(char **ptr);
void				free_triple_pointer(char ***elems);
void				clean_1(t_data *data);
void				clean_2(t_data *data);
void				big_free(t_data *data);

/* ft.c */

char				*ft_strdup(const char *s);
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strcat(char *dest, char *src);
char				*ft_strncat(char *dest, char *src, unsigned int nb);

/* ft_2.c */

char				*ft_strcpy(char *dest, char *src);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strncpy(char *dest, char *src, unsigned int n);
void				*ft_memcpy(void *dest, const void *src, size_t n);

/* split.c */

size_t				ft_strlen(const char *s);
char				**ft_strsplit(char const *s, char *c);

/* print_helpers.c */

void				print_line(char *line);
void				print_tokens(char **token);
void				print_tokens_char_by_char(char **token);
void				print_cmds(char ***cmds);

/* redirection_utils.c */

void				redirect_output(char *file);
void				redirect_append_output(char *file);
void				redirect_input(char *file);

/* get_next_line_utils.c */

void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strchr(const char *s, int c);
char				*get_next_line(int fd);

/* printf_error.c */
void				error_printf(const char *format, const char *str);

/* PARSING */

/* 1-LINE */

/* get_clean_line.c */

char				*modify_line(char *line);

/* utils_operators.c */

int					operator_count(char *line);
int					operator_found(char c);

/* verif_operators.c */

void				get_single_quotes_positions(char *line, int *start,
						int *end);
void				get_double_quotes_positions(char *line, int *start,
						int *end);
int					all_operators_are_inside_quotes(char *line);

/* 2-TOKENIZE */

/* count_tokens.c */

int					token_count(char *line);

/* get_tokens.c */

char				**get_token_array(char *line);

/* quotes_count.c */

int					find_first_quote(char *token, int start, char *quote_type);
int					find_next_quote(char *token, int start, char quote_type);
int					handle_quotes_count(char **tokens, char *line);

/* 3-EXPEND */

/* expend_var.c */

char				*get_envp_value(char **envp, char *found);
void				go_to_expander(char **tokens, char ***envp);
char				*switch_key_to_value(char *tmp_token, char *value,
						int key_len, int prefix_len);

/* found.c */

int					len_of_what_comes_after_dollar(char *token, int pos);
char				*stock_what_comes_after_dollar(char *token, int pos);
int					compare_to_env_variables(char **envp, char *found);
char				*get_envp_value(char **envp, char *found);
int					this_token_has_a_dollar(char *token);

/* lenc.c */

int					get_key_len(char **envp, char *found);
int					len_of_what_comes_before_dollar(char *token, int pos);

/* utils.c */

int					dollar_found_in_array(char **tokens);
int					this_dollar_is_inside_single_quotes_improved(char *line,
						int pos);

/* exp_var_helper1.c */

char				*extract_variable(char *tmp_token, int i);
int					variable_in_envp(char *found, char **envp);
char				*get_value(char *found, char **envp);
char				*replace_variable(char *tmp_token, char *value, int key_len,
						int prefix_len);
char				g_n_char(char *exp_token, int prefix_len, int value_len,
						int exp_len);

/* exp_var_helper2.c */

char				*replace_var_in_token_logic(char *tmp_token, int i,
						char **envp);

/* 4-DEL_QUOTES */

/* get_clean_tokens.c */

char				**return_tokens_without_quotes(char **tokens);
int					get_token_count(char **tokens);

/* quotes_utils.c */

int					quotes_must_be_deleted(char **tokens);
int					get_token_count(char **tokens);
int					find_first_quote_type(char *token, char *quote_type);

/* 5-PARSE.c */

void				process_line(t_data *data);
char				**split_line_according_to_quotes(char *line);
void				prepare_tokens(t_data *data);
void				handle_tokens(t_data *data);
void				clean_3(t_data *data);

/* init_env.c */

char				**get_dup_env(char **envp);
int					check_if_env_i(void);
void				add_default_env_vars(char ***tmp_envp);
void				init_and_configure_data(t_data *data, char **envp);
void				init_ctrl_c(t_data *data);

/* BUILTINS */

int					echo_cmd(char **cmd);
int					pwd_cmd(void);
int					get_env_var_count(char **envp);
char				**get_dup_env(char **envp);
int					env_cmd(char **cmd, char **envp, t_data *data);

int					unset_cmd(char **cmd, char ***envp);
int					export_cmd(char **cmd, char ***envp);
int					cd_cmd(char **path, t_data *data);

int					exit_cmd(char **cmd, t_data *data);
char				**ft_realloc(char **envp, int add_one_size);
int					change_directory(char *path);

/* export_helper.c */

int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					is_valid_var_name(const char *var_name);
char				**ft_realloc(char **envp, int add_one_size);
int					update_var_if_it_exists(char ***tmp_envp, char **split_var,
						char *new_val);
void				add_new_var(char **new_envp, char *new_value);
void				export_with_no_arg(char ***envp);

/* exec_utils.c */

void				big_free1(t_data *data);
void				null_cmd(char **cmd, t_data *data);

/* builtins_filter.c */

void				echo_filter(t_data *data, char **cmd);
void				unset_filter(t_data *data, char **cmd);
void				export_filter(t_data *data, char **cmd);
void				cd_filter(t_data *data, char **cmd);
void				unset_without_env(t_data *data);

/* SIGNALS */

void				signal_handler_parent(void);
void				signal_handler_child(void);

/* EXEC */

/* here_doc */

int					handle_here_doc(char *delimiter, t_data *data);

/*	exec.c	*/

int					count_cmds(t_data *data);
int					ft_is_builtin(char *cmd);
void				ft_exec_builtin(t_data *data, char **cmd);
void				ft_init_exe(t_data *data, int is_last_cmd);
int					builtin_cmd(t_data *data, int saved_stdout);

/* parent_child.c */

int					handle_all_redir(char **cmd, int *i, int *here_doc_fd,
						t_data *data);
int					ft_get_slash(char *str);
void				ft_parent(t_data *data, char **cmd);
void				ft_absolute_cmd(char **cmd, char **envp, t_data *data);
void				ft_execute_command(char **cmd, t_data *data);
void				clean_child(t_data *data);
void				ft_parent_heart(t_data *data);

/* get_cmds.c */

char				***malloc_cmds_array(char **tokens);
char				***create_cmds_array(char **tokens);

/* get_paths.c */

char				*associate_path_to_first_token_of_cmd(char ***cmds,
						int cmd_index);

/* cmd_with_paths.c */

char				***create_final_cmds(t_data *data);

/* exec.c */

void				ft_exec(t_data *data);
void				ft_fork_builtin(t_data *data, char **cmd);
void				ft_init_exe(t_data *data, int is_last_cmd);
void				ft_exec_builtin(t_data *data, char **cmd);

/* exec_helper.c */

void				handle_code_error(t_data *data);
int					cmd_special(t_data *data);
void				regular_cmd(t_data *data, int *i);
int					handle_redir_output_special(t_data *data, int saved_stdout,
						int j);
int					handle_redir_append_special(t_data *data, int saved_stdout,
						int j);

/* minishell.c */

t_data				init_data(char **envp);

#endif
