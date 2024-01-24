/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:10:27 by lbastien          #+#    #+#             */
/*   Updated: 2024/01/24 19:28:58 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(void)
{
	launch_shell();
}

void	launch_shell(void)
{
	char	*input;

	while (1)
	{
		input = readline("ms$> ");
		if (!input)
			break ;
		add_history(input);
		ft_lexer(input);
		free(input);
	}
	printf("Exiting\n");
	return (0);
}
