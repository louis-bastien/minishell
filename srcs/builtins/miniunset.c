/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniunset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:14:59 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/23 11:46:07 by agusheredia      ###   ########.fr       */
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

void	env_rm_var(char *varname, char ***env)
{
	int	index_var;

	index_var = get_var_index(varname, *env);
	if (index_var != -1)
		*env = rm_d_array(*env, index_var);
}

int	mini_unset(t_state *state, char ***env)
{
	int	index_var;

	index_var = get_var_index(state->cmd_list->args[1], *env);
	printf("%s\n", state->cmd_list->args[1]);
	if (state->cmd_list->args_count == 2
		&& index_var != -1)
	{
		env_rm_var(state->cmd_list->args[1], env);
	}
	else
		ft_error_sms("unset no valid\n");
	return (0);
}
