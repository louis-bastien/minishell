/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:28:07 by lbastien          #+#    #+#             */
/*   Updated: 2024/01/29 15:44:27 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum s_ttype
{
	PIPE,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
	WORD
}	t_ttype;

typedef struct s_token
{
	char			*str;
	t_ttype			type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_state
{
	bool		should_terminate;
	t_token		*token_list;
	t_command	*cmd_list;
}	t_state;

typedef struct s_command
{
	char				*command;
	char				**args;
	int					args_count;
	t_token				*tokens;
	int					fd_in;
	int					fd_out;
	struct s_command	*next;
}	t_command;
#endif