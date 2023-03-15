/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:27:37 by mdarify           #+#    #+#             */
/*   Updated: 2023/03/13 19:11:15 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	flen_linked(char *s)
{
	int	l;

	l = 0;
	while (s[l])
	{
		l++;
	}
	return (l);
}

void	fprint_link_error(char *error, int l, int l2)
{
	if (error)
	{
		write(2, error, flen_linked(error));
		write(2, "\n", 1);
	}
	fcode.exit_status = l2;
	if (l)
		exit(l2);
}

int	fbuilt_command_right(t_cmd_node *info, t_env	*env)
{
	int		fd;

	if (fcommand_built(info))
	{
		if (info->io_in > 2)
		{
			fd = dup(1);
			dup2(info->io_in, 1);
		}
		if (fcheck_execv_builtin(info, env))
		{
			if (info->io_out > 2)
			{
				dup2(fd, 1);
				close(info->io_out);
				close(fd);
			}
			return (1);
		}
	}
	return (0);
}

char	**env_arr(t_env_node *env)
{
	t_env_node	*tmp;
	char		**s;
	int			i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	tmp = env;
	s = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (tmp)
	{
		s[i] = ft_strjoin(ft_strjoin(tmp->key, "="), tmp->value);
		tmp = tmp->next;
		i++;
	}
	s[i] = NULL;
	return (s);
}



void	fchild_command_execution(t_cmd_node *data, t_env *env, t_helper *val)
{
	t_env_node	*node;
	int			l;

	node = env->first;
	l = fork();
	if (l == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, &sig_handler);
		if (data->io_in == -1 || data->io_out == -1)
		{
			write(2, "minishell : No such file or directory\n", 39);
				fcode.exit_status = 1;
			exit(fcode.exit_status);
		}
		if (data->io_out > 2)
			dup2(data->io_out, 1);
		else if (val)
			dup2(val->fd[val->i][1], 1);
		if (data->io_in > 2)
			dup2(data->io_in, 0);
		else if (val && val->i != 0)
			dup2(val->fd[val->i - 1][0], 0);
		if (fcheck_execv_builtin(data, env))
			exit(fcode.f_command->fcd);
		while (node)
		{
			if (!ft_strcmp(node->key, "PATH"))
				break ;
			node = node->next;
		}
		if (!env && !ft_strchr(data->cmd_[0], '/'))
			flinked_send_error(2, data->cmd_[0]);
		if (!ft_strchr(data->cmd_[0], '/'))
			fexecute_command(data, env);
		else
			fexecute_command(data, env);
	}
}

void	 flinked_execution_command(t_cmd_node *command, t_env *env)
{
	int	l;

	
	if (fbuilt_command_right(command, env))
		return ;
	if (command->cmd_ && command->args)
		fchild_command_execution(command, env, NULL);
	if (command->io_in > 2)
		close(command->io_in);
	if (command->io_out > 2)
		close(command->io_out);
	fcode.exit_status = 0;
	wait(&l);
	if (l == SIGINT)
		fcode.exit_status = 130;
	else if (l == SIGQUIT)
	{
		printf("Quit: 3\n");
		fcode.exit_status = 131;
	}
		
	else if (WIFEXITED(l))
		fcode.exit_status = WEXITSTATUS(l);
}
