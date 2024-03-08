/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:32:10 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/08 15:15:00 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signals(t_mode mode)
{
	struct sigaction	sa;

	if (mode == EXEC)
		sa.sa_handler = exec_sig_handler;
	else if (mode == NON_EXEC)
		sa.sa_handler = nexec_sig_handler;
	else if (mode == HDOC)
		sa.sa_handler = heredoc_sig_handler;
	sigaction(SIGINT, &sa, NULL);
}

void	exec_sig_handler(int sign)
{
	signal_received = sign;
	if (sign == SIGINT)
		printf("\n");
}

void	nexec_sig_handler(int sign)
{
	signal_received = sign;
	if (sign == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	heredoc_sig_handler(int sign)
{
	signal_received = sign;
	if (sign == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
//		exit(EXIT_FAILURE);
	}
}
