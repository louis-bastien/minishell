/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:22:23 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/09 20:05:27 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCT_H
# define FUNCT_H
# include "minishell.h"

//Main
void		run_shell(t_state *state);
t_state		*init_state(void);

//Lexer
void		ft_lexer(char *input, t_state *state);
void		create_tokens(t_token **token_list, char *input, t_state *state);
void		parse_type(t_token *token);
void		skip_whitespaces(char **str);
char		*generate_token(char **reader, t_state *state);
char		*handle_quotes(char **reader, t_state *state);
char		*handle_string(char **reader, t_state *state);
char		*handle_token(char **reader, t_state *state);
int			is_whitespace(char c);
int			is_quote(char c);
int			is_token(char c);
int			is_single_token(char *str);
int			is_double_token(char *str);
int			is_validchar (char c);

//Expander
void		ft_expander(t_state *state);
char		*expand_env_variables(char *str, t_state *state);
char		*replace_env(char *str, int env_pos, char *value, char *name);
char		*get_env_value(char *name);
char		*get_env_name(char *env, int end_pos);
char		*get_exit_status(char *str);
int			is_valid_env(char c);
void		quote_wrapper(char **str, t_state *state);
void		parse_single_quotes(char **str, char **current, t_state *state);
void		parse_double_quotes(char **str, char **current, t_state *state);
void		remove_char_from_string(char *str, int pos);
char		*expnvar(char **str, int start_pos, int end_pos, t_state *state);

//Parser
void		ft_parser(t_state *state);
void		init_cmd_list(t_token *tokens, t_state *state);
int			add_cmd(t_command **cmd_list, t_token *tokens, int token_counter);
t_command	*create_cmd(t_token *tokens, int token_counter);
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
void		ft_error(char *str, t_state *state);
void		reset_all(t_state *state);
void		free_tokens(t_token	*tokens);
void		free_token(t_token *node);
void		free_cmds(t_command *cmds);
void		free_cmd(t_command *cmd);
void		free_args(t_command *cmd);

//Errors
void		ft_error(char *str, t_state *state);
void		ft_error_sms(char *str);
void		ft_error_perm(int perm, char *str);

//Init
char		**copy_env(char **env);

//Builtins
int			ft_builtins(char **argv, char *envp);
int			minicd(char **argv, char **envp);
int			mini_pwd(t_state *state, char **env);
int			mini_env(int outfd, char **env);

#endif