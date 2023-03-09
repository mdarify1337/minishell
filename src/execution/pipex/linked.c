/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:26:55 by mdarify           #+#    #+#             */
/*   Updated: 2023/03/07 13:33:05 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"


void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	flinked_send_error(int l, char	*command)
{
	if (l == 1)
	{
		ft_putstr_fd("MINISHELL: ERROR 3--->: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd("----command not found-----\n", 2);
		exit(127);
	}
	if (l == 2)
	{
		ft_putstr_fd("MINISHELL: ERROR 4--->: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd("---- No such file or directory ----\n", 2);
		exit(127);
	}
}

int	fcalcule_size(t_cmd_node *command)
{
	t_cmd_node	*minishell;
	int		    l;

	l = 0;
	minishell = command;
	while (minishell)
	{
		minishell = minishell->next;
		l++;
	}
	return (l);
}

void	fexecute_command(t_cmd_node	*minishell, char **path, char **env)
{
	char	*full_path;
	int		i;

	i = -1;
	while (path && path[++i])
	{
		full_path = ft_strjoin(ft_strjoin(path[i], "/"),minishell->cmd_[0]);
		if (access(full_path, F_OK & X_OK) == 0)
			break ;
		free(full_path);
	}
	if (minishell->cmd_[0])
	{
		if (execve(full_path, minishell->cmd_, env) == -1)
			perror("MINISHELL: ---> ERROR1 :---> ");
	}
}
// number of commands

void    ft_execution_command(t_cmd_node   *command, t_env *env)
{
    if (fcalcule_size(command) == 1)
        flinked_execution_command(command, env);
    else if (fcalcule_size(command) > 1)
        flinked_execution_pipex(command, env);
}
