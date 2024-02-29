/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minicd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:48:46 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/28 20:19:54 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_dir_var(t_command *cmd, char ***env)
{
	char	*dir;

	dir = NULL;
	if (cmd->args_count == 1
		|| (ft_strncmp(cmd->args[1], "~", 2) == 0))
	{
		dir = get_var_env("HOME=", *env);
		if (!dir)
			ft_error_perm(42, "cd HOME not set");
	}
	else
		dir = ft_strdup(cmd->args[1]);
	return (dir);
}

char	**update_cd(char ***env)
{
	char	**nenv;
	char	*pwd;
	int		index_pwd;

	index_pwd = get_var_index("PWD", *env);
	pwd = NULL;
	pwd = ft_strjoin("PWD=", getcwd(pwd, sizeof(pwd)));
	nenv = set_darray(*env, pwd, index_pwd);
	return (nenv);
}

int	minicd(t_command *cmd, char ***env)
{
	char	*var;

	var = get_dir_var(cmd, env);
	if (!var)
		return (1);
	if (chdir(var) == -1)
		ft_error_perm(404, var);
	*env = update_cd(env);
	free(var);
	return (0);
}
