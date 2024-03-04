/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:10:27 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/04 16:09:53 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_shell(t_state *state, char ***env)
{
	char				*input;

	while (1)
	{
		ft_signals();
		input = readline("\033[0;32mminishell➜\033[0m ");
		if (!input)
			ft_error("(Input) EOF reached or input error from Readline", state);
		else
		{
			add_history(input);
			ft_lexer(input, state);
			if (!state->error)
				ft_expander(state);
//			print_tokens(state->token_list);
			if (!state->token_list)
				continue;
			if (!state->error)
				ft_parser(state);
			if (!state->error)
				ft_executor(state, env);
//			ft_print_cmds(state->cmd_list);
		}
		reset_all(state);
		free(input);
	}
}

t_state	*init_state(t_state *state)
{
	t_state	*new_state;

	new_state = (t_state *)malloc(sizeof(t_state));
	if (!new_state)
		ft_exit("Failed to malloc t_state", state);
	new_state->error = NULL;
	new_state->token_list = NULL;
	new_state->cmd_list = NULL;
	new_state->data = NULL;
	new_state->num_cmds = 0;
	return (new_state);
}

t_data	*init_data(t_state *state)
{
	t_data	*new_data;

	new_data = malloc(sizeof(t_data));
	if (!new_data)
		ft_exit("Failed to malloc t_data", state);
	new_data->cmd_error = NULL;
	new_data->exit_status = 0;
	new_data->last_pid = -1;
	new_data->childs = 0;
	return (new_data);
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
		printf("SIGINT RECEIVED\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}
