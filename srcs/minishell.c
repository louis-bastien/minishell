/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:10:27 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/08 09:53:20 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_shell(t_state *state, char ***env)
{
	char				*input;

	while (1)
	{
		signal_received = 0;
		ft_signals(NON_EXEC);
		input = readline("\033[0;32mminishell➜\033[0m ");
		if (!input)
			ft_error("(Input) EOF reached or input error from Readline", state);
		else
		{
			pre_shell(state, input);
			if (!state->token_list)
				continue ;
			if (!state->error)
				ft_parser(state);
//			ft_print_cmds(state->cmd_list);
			if (!state->error)
				ft_executor(state, env);
		}
		reset_all(state);
		free(input);
	}
}

void	pre_shell(t_state *state, char *input)
{
	ft_signals(EXEC);
	add_history(input);
	ft_lexer(input, state);
	if (!state->error)
		ft_expander(state);
	//print_tokens(state->token_list);
}
