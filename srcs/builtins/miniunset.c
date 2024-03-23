/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniunset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:14:59 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/23 16:07:21 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	mini_unset(t_command *cmd, char ***env)
{
	int	index_var;
	int	i;

	if (cmd->args_count == 1)
		return (0);
	i = 1;
	while (cmd->args[i])
	{
		index_var = get_var_index(cmd->args[i], *env);
		if (cmd->args_count >= 2
			&& index_var != -1)
			*env = rm_d_array(*env, index_var);
		i++;
	}
	return (0);
}
