/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:22:23 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/21 23:15:49 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCT_H
# define FUNCT_H
# include "minishell.h"

//Main
void		run_shell(t_state *state, char ***env);
void		pre_shell(t_state *state, char *input);
bool		to_continue(t_state *state);
t_state		*init_state(t_state *state);
t_data		*init_data(t_state *state, char **envp);

//Signals
void		ft_signals(t_mode mode);
void		nexec_sig_handler(int sign);
void		stop_sig_handler(int sign);

//Lexer
void		ft_lexer(char *input, t_state *state);
void		create_tokens(t_token **token_list, char *input, t_state *state);
t_ttype		parse_type(char *str);
void		skip_whitespaces(char **str);
char		*generate_token(char **reader, t_state *state);
char		*handle_quotes(char **reader, t_state *state);
char		*handle_string(char **reader, t_state *state);
char		*handle_token(char **reader, t_state *state);
int			get_strlen(char *current);
int			is_whitespace(char c);
int			is_quote(char c);
int			is_token(char c);
int			is_single_token(char *str);
int			is_double_token(char *str);
int			is_validchar(char c);

//Expander
void		ft_expander(t_state *state);
char		*expand_env_variables(char *str, t_state *state);
char		*replace_env(char *str, int env_pos, char *value, char *name);
char		*get_env_value(char *name, t_state *state);
char		*get_env_name(char *env, int end_pos);
int			is_valid_env(char c);
void		quote_wrapper(t_token *token, t_state *state);
void		single_quotes(char **str, char **current, t_state *state);
void		double_quotes(char **str, char **current, t_state *state);
void		unquoted(char **str, char **current, t_state *state);
void		remove_char_from_string(char *str, int pos);
char		*expnvar(char **str, int start_pos, int end_pos, t_state *state);

//Parser
void		ft_parser(t_state *state);
void		init_cmd_list(t_token *tokens, t_state *state);
int			add_cmd(t_command **cmd_list, t_token *tokens, \
			int numtok, int numcmd);
t_command	*create_cmd(t_token *tokens, int numtok, int numcmd);
int			count_upto_pipe(t_token *tokens);
void		handle_redirections(t_command *cmd, t_state *state);
void		handle_heredoc(t_token *token, t_command *cmd, t_state *state);
void		ft_hd_child(char *str, int fd, t_state *state);
void		ft_hd_parent(char *file, int fd, t_command *cmd, t_state *state);
void		parse_fd(t_token *token, t_command *cmd, t_state *state);
void		open_fd(int *fd, const char *filename, int flags, t_state *state);
void		handle_command(t_command *cmd, t_state *state);
void		handle_args(t_command *cmd, t_state *state);

//Token Management
void		ft_parse_tokens(t_state *state);
t_token		*import_tokens(t_token *tokens, int token_counter);
void		remove_token(t_token **token_list, t_token *token);
int			add_token(t_token **token_list, char *str, t_ttype type);
t_token		*create_token(char *str, t_ttype type);
int			count_token(t_token *token);

//Utils 
void		ft_print_cmds(t_command *commands);
void		print_args(t_command *command);
void		print_tokens(t_token *tokens);
char		*print_type(t_ttype type);
int			is_first(t_command *cmd);
int			is_last(t_command *cmd, t_state *state);
void		free_darray(char **d_array);
int			ft_strcmp(const char *str1, const char *str2);
int			ft_strcmp_ignore_nl(const char *str1, const char *str2);
int			ft_export_apend(t_command *cmd, char ***env,
				char **var_value, int i);

//Exit
void		ft_exit(char *str, t_state *state);
void		reset_part(t_state *state);
void		reset_all(t_state *state);
void		free_tokens(t_token	*tokens);
void		free_token(t_token *node);
void		free_cmds(t_command *cmds);
void		free_cmd(t_command *cmd);
void		free_args(t_command *cmd);
void		free_doubleptr(char **dptr);
void		free_env(char ***env);

//Errors
void		ft_error(char *str, t_state *state);
void		ft_error_exec(char *cmd, int exit_code, char *str, t_state *state);
void		print_err(t_state *state);
void		ft_error_perm(int perm, char *str);
void		clear_heredoc(t_state *state);
void		ft_error_builtin(int perm, char *cmd, char *arg);
void		ft_error_exit(int perm, char *arg);
void		put_exit_code(int error_num, t_state *state);
void		ft_error_open(int perm, char *arg);
void		exit_error(int perm, char *cmd, t_state *state);

//Init
char		**copy_env(char **env);

//Builtins
void		check_builtins(t_command *cmd);
int			handle_builtin(t_command *cmd, t_state *state, char ***env);
int			exec_builtin(int fd_out, t_command *cmd, \
			t_state *state, char ***env);
int			minicd(t_command *cmd, char ***env);
int			mini_pwd(char ***env, int fd_out);
int			mini_env(t_command *cmd, char ***env, int fd_out);
int			mini_echo(t_command *cmd, int fd_out);
int			mini_exit(t_state *state, t_command *cmd);
int			mini_export(t_command *cmd, t_state *state, \
			char ***env, int fd_out);
int			mini_unset(t_command *cmd, char ***env);

//utils builtins
void		print_var_res(const char *var, int fd_out);
int			is_env_var_valid(char *word);
char		*get_dir_var(t_command *cmd, char ***env);
void		export_no_arg(char ***env, char **var_export, int fd_out);
char		**update_env(char **var_value, t_command *cmd, char ***env, int i);
int			determine_exit_code(t_state *state, int fd_out);
int			is_str_digit(char *str);
char		**get_varexport(char *var, t_state *state);

//utils data
char		*get_var_env(char *var, char **envp);

//Executor
void		ft_executor(t_state *state, char ***env);
void		make_dup(t_command *cmd, t_state *state);
void		exec_cmd(t_command *cmd, t_state *state, char ***env);
void		ft_child(t_command *cmd, char *path, t_state *state, char ***env);
void		ft_parent(t_command *cmd, int pid, t_state *state);
void		ft_waitpid(t_state *state);
void		ft_init_pipes(t_state *state);
int			needs_pipe(t_command *cmd);
int			assign_pipes(t_command *cmd);
void		ft_execve(t_command *cmd, char *path, t_state *state, char **env);

//Path
char		**ft_parse_path(char **envp);
char		*get_path(t_command *cmd, t_state *state, char **env);
int			is_absolute(t_command *cmd);
int			path_valid(char *path);

//env_utils
int			double_array_size(char **d_str);
char		**set_darray(char **d_str, char *n_str, int index);
int			get_var_index(char *var, char **envp);
char		**addarray(char **d_array, char *nwstr);
char		**rm_d_array(char **d_array, int i);

#endif