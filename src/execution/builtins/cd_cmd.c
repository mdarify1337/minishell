/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounaji <mmounaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:24:04 by mdarify           #+#    #+#             */
/*   Updated: 2023/03/16 21:26:49 by mmounaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	fcd_command_line(char **paths, t_env *env)
{
	t_env	*curr;
	char	buf[256];
	int		ret;

	curr = env;
	ret = 0;
	g_fcode.exit_status = 1;
	if ((!ft_strcmp(paths[0], "cd") && paths[1] == NULL))
		chdir(getenv("HOME"));
	else if ((*paths != NULL && (!ft_strcmp(paths[1], "~"))))
		chdir(getenv("HOME"));
	else
	{
		ret = chdir((const char *)paths[1]);
		if (ret == -1)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			g_fcode.exit_status = 1;
		}	
	}
	getcwd(buf, 256);
}
