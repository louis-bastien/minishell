/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:10:27 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/11 16:34:30 by lbastien         ###   ########.fr       */
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
			ft_error("(Input) EOF reached or input error from Readline", state);
		else
		{
			pre_shell(state, input);
			if (!state->token_list)
				continue ;
			if (to_continue(state))
				ft_parser(state);
//			ft_print_cmds(state->cmd_list);
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
	//print_tokens(state->token_list);
}

bool	to_continue(t_state *state)
{
	if (state->error)
		return (false);
	if (g_signal_received)
		return (false);
	return (true);
}
