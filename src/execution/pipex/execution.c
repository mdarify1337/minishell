/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:27:03 by mdarify           #+#    #+#             */
/*   Updated: 2023/03/09 18:51:20 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int     finitial_variables_commands(t_cmd_node  **command, t_mounaji    *value,\
            t_env    *env)
{
    value->start = 0;
    value->end = 0;
    value->proc = 0;
    value->count = fcalcule_size(*(command)) - 1;
    if (!value->count && fcheck_execv_builtin(*command, env))
        return (0);
    value->fd = malloc(value->count * sizeof(int    *));
    value->pid = malloc((value->count + 1) * sizeof(int ));
    value->i = 0;
    return (1);
}

void	fchild_command_execution2(t_cmd_node *data, t_env *env, t_mounaji *val)
{
	t_env_node	*node;
	int			l;

	node = env->first;
	l = 0;
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (data->io_out > 2)
    {
        close(val->fd[val->i][0]);
        close(val->fd[val->i][1]);
		dup2(data->io_out, 1);
    }
	else if (val->i != val->count)
    {
        close(val->fd[val->i][0]);
		dup2(val->fd[val->i][1], 1);
        close(val->fd[val->i][1]);
    }
	if (data->io_in > 2)
    {
        close(val->fd[val->i - 1][0]);
        close(val->fd[val->i - 1][1]);
        close(val->fd[val->i][0]);
        close(val->fd[val->i][1]);
        dup2(data->io_in, 0);
    }
	else if (val && val->i > 0)
    {
        close(val->fd[val->i - 1][1]);
		dup2(val->fd[val->i - 1][0], 0);
        close(val->fd[val->i - 1][0]);
    }
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
		fexecute_command(data, NULL, env_arr(env->first));
	else
		fexecute_command(data, ft_split(node->value, ':'),
				env_arr(env->first));
}

void    fpclose(t_mounaji   *minishell)
{
    if (minishell->i > 0)
    {
        close(minishell->fd[minishell->i - 1][0]);
        close(minishell->fd[minishell->i - 1][1]);
    }
    else if (minishell->i == minishell->count)
    {
        close(minishell->fd[minishell->i][0]);
        close(minishell->fd[minishell->i][1]);
    }
}

void    fchild_pipe_execution(t_cmd_node   **command, t_mounaji   *val, t_env *env)
{
    if ((*command)->cmd_ && (*command)->cmd_[0])
    {
        val->pid[val->proc] = fork();
        if (val->pid[val->proc] == 0)
            fchild_command_execution2(*(command), env, val);
        (val->proc)++;
    }
    fpclose(val);
    if ((*command)->io_in != 0)
        close((*command)->io_in);
    if ((*command)->io_out != 1)
        close((*command)->io_out);
    val->i++;
    *command = (*command)->next;
}


void    fwait_command(t_mounaji     *minishell)
{
    int l;

    l = 0;
    while (l < minishell->count + 1)
    {
        waitpid(minishell->pid[l], &minishell->status, 0);
        l++;
    }
    if (minishell->status == 2)
        fcode.exit_status = 130;
    else if (minishell->status == 3)
        fcode.exit_status = 131;
    else
        fcode.exit_status = WEXITSTATUS(minishell->status);
    free(minishell->pid);
}

void	flinked_execution_pipex(t_cmd_node *shell, t_env *env)
{
	t_mounaji   *value;

    value = malloc(sizeof (t_mounaji ));
    finitial_variables_commands(&shell, value, env);
    while (shell)
    {
        if (value->i < value->count)
        {
            pipe(value->fd[value->i]);
                value->end++;
        }
        fchild_pipe_execution(&shell, value, env);
    }
    fwait_command(value);
}
