/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:32:10 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/19 19:09:00 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signals(t_mode mode)
{
	if (mode == NON_EXEC)
	{
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
		signal(SIGINT, stop_sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	nexec_sig_handler(int sign)
{
	if (sign == SIGINT)
	{
		g_signal_received = SIGINT;
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	stop_sig_handler(int sign)
{
	write(1, "\n", 1);
	if (sign == SIGINT)
		signal(SIGINT, SIG_IGN);
}
