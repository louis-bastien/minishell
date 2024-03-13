/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minicd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:48:46 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/13 16:19:06 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_dir_var(t_command *cmd, char ***env)
{
	char	*dir;

	dir = NULL;
	if (cmd->args_count == 1
		|| (ft_strcmp(cmd->args[1], "~") == 0))
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
	char	*tmp;
	int		index_pwd;

	index_pwd = get_var_index("PWD", *env);
	if (index_pwd == -1)
		return (*env);
	pwd = NULL;
	tmp = getcwd(pwd, sizeof(pwd));
	pwd = ft_strjoin("PWD=", tmp);
	nenv = set_darray(*env, pwd, index_pwd);
	free(tmp);
	free(pwd);
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
