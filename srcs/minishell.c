/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:10:27 by lbastien          #+#    #+#             */
/*   Updated: 2024/01/26 16:03:46 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_state	*state;

	state = init_state();
	run_shell(state);
}

void	run_shell(t_state *state)
{
	char	*input;

	while (1)
	{
		input = readline("ms$> ");
		if (!input)
			ft_exit("(Input) returned an error or EOF", state);
		add_history(input);
		ft_lexer(input, state);
		ft_parser(state);
		free(input);
	}
}

t_state	*init_state(void)
{
	t_state	*new_state;

	new_state = malloc(sizeof(t_state));
	new_state->should_terminate = false;
	new_state->token_list = NULL;
	new_state->cmd_list = NULL;
}
