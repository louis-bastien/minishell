/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniunset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:14:59 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/14 11:16:55 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_env_var_valid(char *word)
{
	int	i;

	i = 0;
	if (!word || !word[i])
		return (1);
	if (word[i] == '_' || ft_isalpha(word[i]))
	{
		i++;
		while (word[i] == '_' || ft_isalpha(word[i]) || ft_isdigit(word[i]))
			i++;
	}
	if (word[i] == '\0')
		return (0);
	return (1);
}

int	mini_unset(t_state *state)
{
	if (state->cmd_list->args_count == 2
		&& is_env_var_valid(state->cmd_list->args[1]))
	{
		printf("aqui deberia borrar var\n");
		unsetenv(state->cmd_list->args[1]);
	}
	else
		ft_error_sms("unset no valid\n");
	return (0);
}
