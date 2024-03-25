/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniexit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:10:31 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/25 14:47:43 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_numeric(char *inp)
{
	while (*inp && (*inp == ' '))
		inp++;
	if (!*inp)
		return (0);
	if ((*inp == '-' || *inp == '+') && !(*(inp + 1)))
		return (0);
	if (*inp == '-' || *inp == '+')
		inp++;
	while (*inp && ft_isdigit(*inp))
		inp++;
	while (*inp && (*inp == ' '))
		inp++;
	if (*inp)
		return (0);
	return (1);
}

static bool	valid_numeric_argv(char *data)
{
	bool	neg;

	neg = 0;
	if (!is_numeric(data) || *data == 0)
		return (0);
	if (*data == '-')
		neg = 1;
	if (*data == '-' || *data == '+')
		data++;
	while (*data && *(data + 1) && *data == '0')
		data++;
	if (ft_strlen(data) > 19)
		return (0);
	if (ft_strlen(data) < 19)
		return (1);
	if (!neg && ft_strncmp(data, "9223372036854775807", 0xffffffff) <= 0)
		return (1);
	if (neg && ft_strncmp(data, "9223372036854775808", 0xffffffff) <= 0)
		return (1);
	return (0);
}

int	determine_exit_code(t_state *state, t_command *cmd, int fd_out)
{
	int			exit_code;

	exit_code = 1;
	if (!cmd->args[1])
		exit_code = 0;
	else if (valid_numeric_argv(cmd->args[1]))
		exit_code = ft_atol(cmd->args[1]);
	else
	{
		ft_putstr_fd("exit\n", fd_out);
		ft_error_exit(55, cmd->args[1]);
		state->data->exit_status = 255;
		ft_exit(NULL, state);
	}
	return (exit_code);
}

int	mini_exit(t_state *state, t_command *cmd)
{
	if (cmd->args_count > 2)
	{
		if (valid_numeric_argv(cmd->args[1]))
		{
			ft_putstr_fd("exit\n", cmd->fd_out);
			ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
			state->data->exit_status = 1;
			return (1);
		}
	}
	free_darray(state->data->env);
	free_darray(state->data->vexp);
	state->data->exit_status = determine_exit_code(state, cmd, cmd->fd_out);
	ft_putstr_fd("exit\n", cmd->fd_out);
	ft_exit(NULL, state);
	return (0);
}
