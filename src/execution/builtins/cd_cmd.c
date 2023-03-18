/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:24:04 by mdarify           #+#    #+#             */
/*   Updated: 2023/03/18 07:42:44 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	fcd_check_error(char **path, t_env *env)
{
	(void)path;
	if (!search_by_key(env->first, "HOME"))
	{
		fprint_ecode("minishell : cd : HOME not set\n", 2, g_fcode.exit_status);
		g_fcode.exit_status = 1;
		return ;
	}
}

void	fpwrite(void)
{
	ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	g_fcode.exit_status = 1;
}

void	linked_fcd(t_env	*env, char	**paths)
{
	char	buf[256];
	char	*val;

	fcd_check_error(paths, env);
	if (chdir(getenv("HOME")) == 0)
	{
		val = getcwd(buf, 256);
		if (!search_by_key(env->first, "PWD"))
		{
			insert_to_tail(&env, env_new("PWD="));
			(search_by_key(env->first, "OLDPWD")->value) = "";
		}
		(search_by_key(env->first, "OLDPWD")->value) \
		= (search_by_key(env->first, "PWD")->value);
		search_by_key(env->first, "PWD")->value = ft_strdup(val);
	}
}

void	fcd_command_line(char **paths, t_env *env)
{
	t_env	*curr;
	char	*val;
	char	buf[256];
	int		ret;

	curr = env;
	ret = 0;
	val = NULL;
	g_fcode.exit_status = 1;
	if ((!ft_strcmp(paths[0], "cd") && paths[1] == NULL))
		linked_fcd(env, paths);
	else
	{
		ret = chdir((const char *)paths[1]);
		if (ret == -1)
			fpwrite();
		(search_by_key(env->first, "OLDPWD")->value) \
		= (search_by_key(env->first, "PWD")->value);
			val = getcwd(buf, 256);
		search_by_key(env->first, "PWD")->value = ft_strdup(val);
	}
}
