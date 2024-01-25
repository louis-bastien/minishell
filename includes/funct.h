/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:22:23 by lbastien          #+#    #+#             */
/*   Updated: 2024/01/25 17:02:39 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCT_H
# define FUNCT_H
# include "minishell.h"

//Main
void	run_shell(t_state *state);

//Exit
void	ft_exit(char *str, t_state *state);
void	free_items(t_item	*items);
void	free_node(t_item *node);

//Lexer
void	ft_lexer(char *input, t_state *state);
void	ft_lexer_reader(t_token **item_list, char *input, t_state *state);
int		add_item(t_item **item_list, char *str);
t_item	*create_item(char *str);
void	ft_tokenise(t_token *item);
t_token	identify_token(char *str);

//Parser


//Utils 
int		ft_strlen(const char *str);
int		is_whitespace(char c);

#endif