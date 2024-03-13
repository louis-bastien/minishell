/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:42:06 by agusheredia       #+#    #+#             */
/*   Updated: 2024/03/13 12:22:47 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

int	main(int argc, char **argv, char **envp)
{
	t_state	*state;

	state = NULL;
	state = init_state(state);
	state->data = init_data(state, envp);
	if (argc != 1 && argv[1])
		ft_exit("Minishell does not take any argument.", state);
	else
		run_shell(state, &state->data->env);
	ft_exit("Exiting from main", state);
	return (0);
}
