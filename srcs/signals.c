/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:32:10 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/11 16:51:52 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signals(t_mode mode)
{
	if (mode == NON_EXEC)
	{
		signal_received = 0;
		signal(SIGINT, nexec_sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == EXEC)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == STOP)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	nexec_sig_handler(int sign)
{
	signal_received = sign;
	if (sign == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}
