/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:28:07 by lbastien          #+#    #+#             */
/*   Updated: 2024/01/25 17:02:46 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum s_token
{
	PIPE,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
	WORD
}	t_token;

typedef struct s_item
{
	char			*str;
	t_token			token;
	int				index;
	struct s_item	*next;
}	t_item;

typedef struct s_state
{
	bool		should_terminate;
	t_item		*item_list;
	t_command	*cmds;
}	t_state;

typedef struct s_command
{
	char	*command;
	char	**args;
	int		args_count;
	t_item	*items;
	char	*infile;
	char	*outfile;
	struct s_command *next;
}	t_command;
#endif