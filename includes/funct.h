/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:22:23 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/20 11:59:06 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCT_H
# define FUNCT_H
# include "minishell.h"

//Main
void		run_shell(t_state *state);
t_state		*init_state(t_state *state);
t_data		*init_data(char **envp, t_state *state);

//Lexer
void		ft_lexer(char *input, t_state *state);
void		create_tokens(t_token **token_list, char *input, t_state *state);
void		parse_type(t_token *token);
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
char		*get_env_value(char *name);
char		*get_env_name(char *env, int end_pos);
char		*get_exit_status(char *str);
int			is_valid_env(char c);
void		quote_wrapper(t_token *token, t_state *state);
void		single_quotes(char **str, char **current, t_state *state);
void		double_quotes(char **str, char **current, t_state *state);
void		unquoted(char **str, char **current, \
			t_token *token, t_state *state);
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
void		parse_fd(t_token *token, t_command *cmd, t_state *state);
void		open_fd(int *fd, const char *filename, int flags, t_state *state);
void		handle_command(t_command *cmd, t_state *state);
void		handle_args(t_command *cmd, t_state *state);

//Token Management
void		ft_parse_tokens(t_state *state);
t_token		*import_tokens(t_token *tokens, int token_counter);
void		remove_token(t_token **token_list, t_token *token);
int			add_token(t_token **token_list, char *str);
t_token		*create_token(char *str);
int			count_token(t_token *token);


//Utils 
void		ft_print_cmds(t_command *commands);
void		print_args(t_command *command);
void		print_tokens(t_token *tokens);
char		*print_type(t_ttype type);

//Exit
void		ft_exit(char *str, t_state *state);
void		reset_all(t_state *state);
void		free_tokens(t_token	*tokens);
void		free_token(t_token *node);
void		free_cmds(t_command *cmds);
void		free_cmd(t_command *cmd);
void		free_args(t_command *cmd);
void		free_data(t_data *data);
void		free_doubleptr(char **dptr);

//Errors
void		ft_error(char *str, t_state *state);
void		ft_error_exec(char *cmd, int exit_code, char *str, t_state *state);
void		print_err(t_state *state);
void		ft_error_sms(char *str);
void		ft_error_perm(int perm, char *str);

//Init
char		**copy_env(char **env, t_state *state);
void		is_builtins(t_state *state);

//Builtins
void		check_builtins(t_command *cmd);
void		ft_exec_builtin(t_state *state, t_command *cmd);
int			minicd(t_state *state);
int			mini_pwd(t_state *state);
int			mini_env(t_state *state);
int			mini_echo(t_state *state);
int			mini_exit(t_state *state);
int			mini_export(t_state *state);
int			mini_unset(t_state *state);

//utils builtins
void		print_var_res(int outfd, const char *var);
int			is_env_var_valid(char *word);
char		*get_dir_var(t_state *state);
void		export_no_arg(t_state *state);
char		**update_env(char **var_value, t_state *state);
//void		rm_var(char *var, char **env);

//utils data
char		*get_var_env(char *var, char **envp);
char		**ft_parse_path(char **envp);
char		*get_path(char **all_path, char *cmd);

//Executor
void		pre_executor(t_state *state);
void		one_cmd(t_state *state);
void		exec_cmd(t_command *cmd, t_state *state);  

void		ft_init_pipes(t_state *state);
int			needs_pipe(t_command *cmd);
int			assign_pipes(t_command *cmd);

//env_utils
int			double_array_size(char **d_str);
char		**set_darray(char **d_str, char *n_str, int index);
int			get_var_index(char *var, char **envp);
char		**add_str_darry(char **d_array, char *nwstr);

#endif