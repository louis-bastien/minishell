/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:28:07 by lbastien          #+#    #+#             */
/*   Updated: 2024/01/26 11:32:54 by lbastien         ###   ########.fr       */
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
	t_ttype			token;
	int				index;
	struct s_token	*next;
}	t_token;

typedef struct s_state
{
	bool		should_terminate;
	t_token		*token_list;
	t_command	*cmds;
}	t_state;

typedef struct s_command
{
	char	*command;
	char	**args;
	int		args_count;
	t_token	*items;
	char	*infile;
	char	*outfile;
	struct s_command *next;
}	t_command;
#endif