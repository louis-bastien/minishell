/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniexit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:10:31 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/15 14:56:55 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_str_digit(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (0);
	if ((str[i] == '-' || str[i] == '+') && str[i + 1])
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			flag = 1;
		i++;
	}
	if (str[--i] == ' ' && flag == 1)
		flag = 0;
	if (flag == 1)
		return (0);
	return (1);
}

int	determine_exit_code(t_state *state)
{
	int			exit_code;

	exit_code = 1;
	if (!state->cmd_list->args[1])
		exit_code = 0;
	else if (is_str_digit(state->cmd_list->args[1]))
	{
		if (ft_strlen(state->cmd_list->args[1]) > 17)
		{
			ft_error_exit(55, state->cmd_list->args[1]);
			state->data->exit_status = 255;
			ft_exit(NULL, state);
		}
		else
			exit_code = ft_atol(state->cmd_list->args[1]);
	}
	else
	{
		ft_error_exit(55, state->cmd_list->args[1]);
		state->data->exit_status = 255;
		ft_exit(NULL, state);
	}
	return (exit_code);
}

int	mini_exit(t_state *state, t_command *cmd)
{
	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("Minishell: exit: too many argumnets\n", 2);
		return (1);
	}
	free_darray(state->data->env);
	state->data->exit_status = determine_exit_code(state);
	ft_exit("exit", state);
	return (0);
}
