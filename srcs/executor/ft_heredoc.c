/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:34:49 by agheredi          #+#    #+#             */
/*   Updated: 2024/01/30 11:37:06 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_here_doc(char *argv)
{
	int		infile;
	char	*buf;

	infile = open(".here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (infile < 0)
		ft_error_sms("Error here_doc\n");
	while (1)
	{
		write(1, "heredoc> ", 9);
		buf = get_next_line(STDIN_FILENO);
		if (!buf)
			exit (1);
		if (!ft_strncmp(argv, buf, ft_strlen(argv)))
			break ;
		write(infile, buf, ft_strlen(buf));
		write(infile, "\n", 1);
		free(buf);
	}
	free(buf);
	close(infile);
}
