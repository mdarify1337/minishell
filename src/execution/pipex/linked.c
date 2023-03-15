/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:26:55 by mdarify           #+#    #+#             */
/*   Updated: 2023/03/13 21:03:58 by mdarify          ###   ########.fr       */
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

void	flinked_send_error(int l, char *command)
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
	int			l;

	l = 0;
	minishell = command;
	while (minishell)
	{
		minishell = minishell->next;
		l++;
	}
	return (l);
}

char	*st_join(char const *s1, char crt, char const *s2)
{
	char	*str;
	size_t	x;
	size_t	y;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	x = 0;
	y = 0;
	while (s1[y])
		str[x++] = s1[y++];
	str[x++] = crt;
	y = 0;
	while (s2[y])
		str[x++] = s2[y++];
	str[x] = '\0';
	return (str);
}

char	*get_cmd(char **paths, char *cmd, t_env *env)
{
	char		**tmp;
	char		*command;
	t_env_node	*pwd;

	if (cmd[0] == '/')
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		else
		{
			fprint_ecode("No such file or directory\n", 2,
					fcode.exit_status);
			fcode.exit_status = 127;
			exit(fcode.exit_status);
		}
	}
	else if (cmd[0] == '.')
	{
		pwd = search_by_key(env->first, "PWD");
		command = st_join(pwd->value, '/', cmd);
		if (access(command, X_OK) == 0)
			return (command);
		else
			printf("minishell: %s: No such file or directory\n", cmd);
	}
	else
	{
		tmp = paths;
		while (*tmp != NULL)
		{
			command = st_join(*tmp, '/', cmd);
			tmp++;
			if (access(command, X_OK) == 0)
			{
				free_2d_array(paths);
				return (command);
			}
			free(command);
		}
	}
	free_2d_array(paths);
	return (NULL);
}

int	find_path(t_cmd_node **cmd, t_env *env)
{
	t_env_node	*node;
	char		*abs_path;

	node = search_by_key(env->first, "PATH");
	if (!node)
		return (0);
	abs_path = get_cmd(ft_split(node->value, ':'), (*cmd)->args, env);
	if (abs_path == NULL)
	{
		fprint_ecode("MINISHELL : command not found---->\n", 2, 127);
		fcode.exit_status = 127;
		exit(127);
	}
	else if (abs_path)
	{
		free((*cmd)->args);
		(*cmd)->args = ft_strdup(abs_path);
		free(abs_path);
		return (1);
	}
	return (fcode.exit_status);
}

void	fexecute_command(t_cmd_node *minishell, t_env *env)
{
	if ((find_path(&minishell, env)) == 1)
	{
		fcode.exit_status = 127;
	}
	if (minishell->cmd_[0])
	{
		if (execve(minishell->args, minishell->cmd_, convert_array(env)) == -1)
		{
			fprint_ecode("minishell : command not found \n", 2, fcode.exit_status);
			fcode.exit_status = 127;
			exit(fcode.exit_status);
		}
	}
}
// number of commands

void	ft_execution_command(t_cmd_node *command, t_env *env)
{
	if (command)
	{
		if (fcalcule_size(command) == 1)
			flinked_execution_command(command, env);
		else if (fcalcule_size(command) > 1)
			flinked_execution_pipex(command, env);
	}
}
