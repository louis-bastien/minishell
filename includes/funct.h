/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:22:23 by lbastien          #+#    #+#             */
/*   Updated: 2024/01/26 15:48:52 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCT_H
# define FUNCT_H
# include "minishell.h"

//Main
void		run_shell(t_state *state);

//Lexer
void		ft_lexer(char *input, t_state *state);
void		ft_lexer_reader(t_token **token_list, char *input, t_state *state);
int			add_token(t_token **token_list, char *str);
t_token		*create_token(char *str);
void		tokenise(t_token *token);

//Parser
void		ft_parser(t_state *state);
void		init_cmds(t_token *tokens, t_state *state);
int			add_cmd(t_command **cmds, t_token *tokens, int token_counter);
t_command	*create_cmd(t_token *tokens, int token_counter);
int			count_upto_pipe(t_token *tokens);

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

#endif