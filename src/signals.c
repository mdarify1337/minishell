/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:05:23 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/07 10:03:51 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handler(int sig)
{
	(void)sig;
	printf("<<<<\n");
}

void	init_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &sig_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGKILL);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGKILL, &sa, NULL);
}
/*
char	*get_path(char **path, char *cmd)
{
	int	i;

	i = 0;
	if (!cmd[0])
		error_msg(1, cmd);
	if (!path)
		error_msg(2, cmd);
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], cmd);
		if (access(path[i], F_OK) == 0)
		{
			return (path[i]);
		}
		i++;
	}
	return (NULL);
}

void	ft_execute(t_cmd *a, char **path)
{
	char	*cmd_path;

	if (a->cmd_option[0])
	{
		if (!access(a->cmd_option[0], F_OK) && ft_strchr(a->cmd_option[0], '/'))
		{
			if (execve(a->cmd_option[0], a->cmd_option, g_glob.env) == -1)
				perror("minishell");
			exit(126);
		}
		cmd_path = get_path(path, a->cmd_option[0]);
		if (!cmd_path)
			error_msg(1, a->cmd_option[0]);
		free(path);
		if (execve(cmd_path, a->cmd_option, g_glob.env) == -1)
			perror("minishell");
	}
}
*/