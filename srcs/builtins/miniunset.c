/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniunset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:14:59 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/09 20:42:26 by agusheredia      ###   ########.fr       */
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

/*void	rm_var(char *var, char **env)
{
	
}*/

int	mini_unset(t_state *state)
{
	int	i;

	i = 0;
	while (state->cmd_list->args[i])
	{
		if (is_env_var_valid(state->cmd_list->args[i]))
		{
			printf("aqui deberia borrar var\n");
			//rm_var(argv[i], env);
		}
		else
			ft_error_sms("unset no valid\n");
	}
	return (0);
}
