/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounaji <mmounaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:47:05 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/17 20:14:50 by mmounaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_sort(t_env *env)
{
	t_env_node	*current;

	current = env->first;
	while (current->next)
	{
		if (ft_strcmp(current->key, current->next->key) > 0)
		{
			ft_swap(current, current->next);
			current = env->first;
		}
		else
			current = current->next;
	}
}

void	print_env_sorted(t_env *env)
{
	t_env_node	*current;

	if (!env->first)
		return ;
	ft_sort(env);
	current = env->first;
	while (current)
	{
		printf("declare -x %s", current->key);
		if (current->value != NULL)
			printf("=\"%s\"", current->value);
		printf("\n");
		current = current->next;
	}
}

void	export_cmd(t_env	*env, char *arg, int i)
{
	t_env_node	*node;
	t_env_node	*node_;

	node = env->first;
	if (!arg)
		print_env_sorted(env);
	else if (!arg || !ft_is_alpha(arg[0]))
	{
		printf("minishell : export : `%s` not a valid identifier", arg);
		g_fcode.exit_status = 1;
	}
	else if (arg[i - 1] && arg[i - 1] == '+')
		export_with_join(&env, arg, i, NULL);
	else if (!node)
		insert_to_tail(&env, env_new(arg));
	else if (i != -1 && search_by_key(node, ft_substr(arg, 0, i)) != NULL)
	{
		node_ = search_by_key(node, ft_substr(arg, 0, i));
		if (node_)
			free(node_->value);
			node_->value = ft_substr(arg, i + 1, ft_strlen(arg) - i);
	}
	else if (search_by_key(node, ft_strdup(arg)) == NULL)
		insert_to_tail(&env, env_new(arg));
}

void	exec_export(t_cmd_node *cmd, t_env **env)
{
	int	i;

	i = 1;
	if (cmd->cmd_[i] == NULL)
	{
		export_cmd(*env, NULL, 1);
		return ;
	}
	while (cmd->cmd_[i])
	{
		export_cmd(*env, cmd->cmd_[i], ft_strchr(cmd->cmd_[i], '='));
		i++;
	}
}
