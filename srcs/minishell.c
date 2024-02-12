/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:10:27 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/12 13:10:57 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_state	*state;

	state = init_state(envp);
	if (argc > 1 || argv[1])
		perror("Minishell does not take any argument.");
	else
		run_shell(state);
	free(state);
	state = NULL;
	return (1);
}

void	run_shell(t_state *state)
{
	char	*input;

	while (1)
	{
		input = readline("minishell_$> ");
		if (!input)
			ft_error("(Input) EOF reached or input error from Readline", state);
		else
		{
			add_history(input);
			ft_lexer(input, state);
			if (!state->error)
				ft_expander(state);
			if (!state->error)
				ft_parser(state);
			if (!state->error)
				pre_executor(state);
		ft_print_cmds(state->cmd_list);
		}
		reset_all(state);
		free(input);
	}
}

t_state	*init_state(char **envp)
{
	t_state	*new_state;

	new_state = (t_state *)malloc(sizeof(t_state));
	new_state->error = NULL;
	new_state->token_list = NULL;
	new_state->cmd_list = NULL;
	new_state->data = malloc(sizeof(t_data));
	if (!new_state->data)
		ft_error_sms("Error: No se pudo asignar memoria.\n");
	new_state->data->env = copy_env(envp);
	new_state->data->path = ft_parse_path(envp);
	return (new_state);
}
