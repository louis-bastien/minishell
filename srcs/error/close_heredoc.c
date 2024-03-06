/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:36:58 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/06 13:20:24 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_heredoc(t_state *state)
{
	char	*file;

	while (state->heredoc)
	{
		file = ft_strjoin(".heredoc", ft_itoa(state->heredoc));
		unlink(file);
		state->heredoc--;
	}
}
