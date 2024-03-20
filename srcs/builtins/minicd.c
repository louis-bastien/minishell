/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minicd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:48:46 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/20 12:55:56 by agheredi         ###   ########.fr       */
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
			ft_error_perm(42, "cd HOME not set\n");
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
	if (!tmp)
		return (*env);
	pwd = ft_strjoin("PWD=", tmp);
	nenv = set_darray(*env, pwd, index_pwd);
	free(tmp);
	return (nenv);
}

int	minicd(t_command *cmd, char ***env)
{
	char	*var;
	int		state;

	state = 0;
	var = get_dir_var(cmd, env);
	if (!var)
		return (1);
	if (chdir(var) == -1)
	{
		state = 1;
		ft_error_builtin(404, "cd", cmd->args[1]);
	}
	*env = update_cd(env);
	free(var);
	return (state);
}
