/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounaji <mmounaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 18:03:31 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/17 18:00:46 by mmounaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_env_node(t_env_node *e)
{
	free(e->key);
	free(e->value);
	free(e);
}

int	delete_node_by_key(t_env *head, char *key)
{
	t_env_node	*tmp;

	if (!head->first ||!key)
		return (0);
	tmp = head->first;
	if (ft_strcmp(tmp->key, key) == 0)
	{
		head->first = tmp->next;
		head->first->previous = NULL;
		free_env_node(tmp);
		return (0);
	}
	while (tmp && ft_strcmp(tmp->key, key) != 0)
		tmp = tmp->next;
	if (tmp != NULL)
	{
		tmp->previous->next = tmp->next;
		tmp->next->previous = tmp->previous;
		free_env_node(tmp);
		return (1);
	}
	return (0);
}

int	unset_cmd(t_env *env, char *key)
{
	return (delete_node_by_key(env, key));
}

void	exec_unset(t_cmd_node *cmd, t_env **env)
{
	int	i;

	i = 1;
	if (cmd->cmd_[i] == NULL)
		return ;
	while (cmd->cmd_[i])
	{
		unset_cmd(*env, cmd->cmd_[i]);
		i++;
	}
}
