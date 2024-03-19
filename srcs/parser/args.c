/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:16:02 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/19 15:01:09 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_command(t_command *cmd, t_state *state)
{
	t_token	*current;

	current = cmd->tokens;
	if (!current || current->type != WORD)
		return ;
	else
	{
		cmd->command = ft_strdup(current->str);
		if (!cmd->command)
			ft_error("(parser) Failed to malloc command", state);
	}
}

void	handle_args(t_command *cmd, t_state *state)
{
	t_token	*current;
	t_token	*next;
	int		i;

	i = 0;
	current = cmd->tokens;
	next = NULL;
	cmd->args_count = count_token(current);
	if (cmd->args_count == 0)
		return ;
	cmd->args = malloc(sizeof(char *) * (cmd->args_count + 1));
	if (!cmd->args)
		ft_error("(parser) Failed to malloc args", state);
	while (i < cmd->args_count)
	{
		next = current->next;
		cmd->args[i] = ft_strdup(current->str);
		if (!cmd->args[i])
			ft_error("(parser) Failed to malloc arg", state);
		remove_token(&cmd->tokens, current);
		current = next;
		i++;
	}
	cmd->args[i] = NULL;
}

void	check_builtins(t_command *cmd)
{
	if (!cmd->command)
		return ;
	else if (!ft_strncmp(cmd->command, "cd", 3))
		cmd->is_builtin = true;
	else if (!ft_strncmp(cmd->command, "pwd", 4))
		cmd->is_builtin = true;
	else if (!ft_strncmp(cmd->command, "echo", 5))
		cmd->is_builtin = true;
	else if (!ft_strncmp(cmd->command, "export", 7))
		cmd->is_builtin = true;
	else if (!ft_strncmp(cmd->command, "unset", 6))
		cmd->is_builtin = true;
	else if (!ft_strncmp(cmd->command, "env", 4))
		cmd->is_builtin = true;
	else if (!ft_strncmp(cmd->command, "exit", 5))
		cmd->is_builtin = true;
	else
		cmd->is_builtin = false;
}
