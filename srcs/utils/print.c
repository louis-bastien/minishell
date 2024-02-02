/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:35:13 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/02 15:35:59 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_cmds(t_command *commands)
{
	int	index;

	index = 0;
	while (commands)
	{
		printf("#COMMAND STRUCT %d-\n", index);
		printf("command: %s\n", commands->command);
		print_args(commands);
		printf("args_count: %d\n", commands->args_count);
		print_token(commands->tokens);
		printf("fd_in: %d\n", commands->fd_in);
		printf("fd_out: %d\n", commands->fd_out);
		printf("==\n");
		index++;
		commands = commands->next;
	}
}

void	print_args(t_command *command)
{
	int	i;

	i = 0;
	printf("args: ");
	while (i < command->args_count)
	{
		printf("%s(%d) ", command->args[i], i);
		i++;
	}
	printf("\n");
}

void	print_token(t_token *tokens)
{
	printf("tokens: ");
	while (tokens)
	{
		printf("%s(%s) ", tokens->str, print_type(tokens->type));
		tokens = tokens->next;
	}
	printf("\n");
}

char	*print_type(t_ttype type)
{
	if (type == PIPE)
		return ("PIPE");
	else if (type == INPUT)
		return ("INPUT");
	else if (type == OUTPUT)
		return ("OUTPUT");
	else if (type == HEREDOC)
		return ("HEREDOC");
	else if (type == APPEND)
		return ("APEND");
	else if (type == WORD)
		return ("WORD");
	else
		return ("ERROR");
}