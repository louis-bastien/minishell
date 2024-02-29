/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:42:06 by agusheredia       #+#    #+#             */
/*   Updated: 2024/02/28 19:43:33 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_state	*state;
	char	**env;

	(void)argv;
	state = NULL;
	state = init_state(state);
	state->data = init_data(state);
	env = copy_env(envp);
	if (argc != 1)
		ft_exit("Minishell does not take any argument.", state);
	else
		run_shell(state, &env);
	ft_exit("Exiting from main", state);
	return (0);
}
