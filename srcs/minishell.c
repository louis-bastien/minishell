/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:10:27 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/20 13:49:15 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_shell(t_state *state, char ***env)
{
	char				*input;

	while (1)
	{
		ft_signals(NON_EXEC);
		input = readline("minishell-> ");
		if (!input)
		{
			write(1, "exit\n", 5);
			exit(state->data->exit_status);
		}
		else
		{
			pre_shell(state, input);
			if (!state->token_list)
				continue ;
			if (to_continue(state))
				ft_parser(state);
			if (to_continue(state))
				ft_executor(state, env);
		}
		reset_all(state);
		free(input);
	}
}

void	pre_shell(t_state *state, char *input)
{
	add_history(input);
	ft_lexer(input, state);
	if (to_continue(state))
		ft_expander(state);
}

bool	to_continue(t_state *state)
{
	if (state->error)
		return (false);
	if (state->to_stop)
		return (false);
	return (true);
}
