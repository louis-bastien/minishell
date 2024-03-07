/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:10:27 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/07 11:46:51 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_shell(t_state *state, char ***env)
{
	char				*input;

	while (1)
	{
		ft_signals();
		g_command_running = 0;
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
			//ft_print_cmds(state->cmd_list);
			if (!state->error)
				ft_executor(state, env);
		}
		reset_all(state);
		free(input);
	}
}

void	pre_shell(t_state *state, char *input)
{
	g_command_running = 1;
	add_history(input);
	ft_lexer(input, state);
	if (!state->error)
		ft_expander(state);
	//print_tokens(state->token_list);
}

void	ft_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

void	signal_handler(int sign)
{
	if (sign == SIGINT)
	{
		printf("\n");
		if (!g_command_running)
		{
			rl_replace_line("", 1);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}
