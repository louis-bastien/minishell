/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:28:07 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/06 13:19:28 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define NOFILE 404
# define NOREAD 403
# define NOWRITE 402
# define NOCMD 127

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

typedef struct s_command
{
	char				*command;
	char				**args;
	int					index;
	int					args_count;
	t_token				*tokens;
	int					fd_in;
	int					fd_out;
	bool				is_builtin;
	struct s_command	*next;
}	t_command;

typedef struct s_data
{
	pid_t	pid;
	char	*cmd_error;
	int		exit_status;
	int		childs;
	int		last_pid;
	char	**env;
}	t_data;

typedef struct s_state
{
	char		*error;
	t_token		*token_list;
	t_command	*cmd_list;
	t_data		*data;
	int			heredoc;
	int			num_cmds;
}	t_state;

#endif