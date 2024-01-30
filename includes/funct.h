/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:22:23 by lbastien          #+#    #+#             */
/*   Updated: 2024/01/30 11:27:11 by agheredi         ###   ########.fr       */
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
void		ft_lexer_reader(t_token **token_list, char *input, t_state *state);
void		tokenise(t_token *token);

//Parser
void		ft_parser(t_state *state);
void		init_cmd_list(t_token *tokens, t_state *state);
int			add_cmd(t_command **cmd_list, t_token *tokens, int token_counter);
t_command	*create_cmd(t_token *tokens, int token_counter);
int			count_upto_pipe(t_token *tokens);
void		handle_redirections(t_command *cmd, t_state *state);

//Token Management
void		ft_parse_tokens(t_state *state);
t_token		*import_tokens(t_token *tokens, int token_counter);
void		remove_token(t_token **token_list, t_token *token);
int			add_token(t_token **token_list, char *str);
t_token		*create_token(char *str);

//Utils 
int			ft_strlen(const char *str);
int			is_whitespace(char c);

//Exit
void		ft_exit(char *str, t_state *state);
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

#endif