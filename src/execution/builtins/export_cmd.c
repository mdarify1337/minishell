/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:47:05 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/04 21:32:03 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	find_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_swap(t_env_node *n1, t_env_node *n2)
{
	char	*key;
	char	*val;

	key = n1->key;
	val = n1->value;
	n1->key = n2->key;
	n1->value = n2->value;
	n2->key = key;
	n2->value = val;
}

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
	t_env		*tmp;
	t_env_node	*current;

	tmp = env;
	ft_sort(tmp);
	current = tmp->first;
	while (current)
	{
		printf("declare -x %s", current->key);
		if (current->value != NULL)
			printf("=\"%s\"", current->value);
		printf("\n");
		current = current->next;
	}
}

void	export_cmd(t_env	*env, char **arg)
{
	t_env_node	*node_;
	t_env_node	*node;
	int			i;

	node = env->first;
	i = ft_strchr(arg[2], '=');
	if (!arg[2])
		print_env_sorted(env);
	else if (!arg[2] || !ft_is_alpha(arg[2][0]))
		perror("minishell : export : `%s` not a valid identifier");
	else if (i != -1 && search_by_key(node, ft_substr(arg[2], 0, i)))
	{
		node_ = search_by_key(node, ft_substr(arg[2], 0, i));
		if (node_ && node_->value != NULL)
		{
			free(node_->value);
			node_->value = ft_substr(arg[2], i + 1, ft_strlen(arg[2]) - i);
		}
	}
	else if (i == -1 && !search_by_key(node, arg[2]))
		insert_to_tail(&env->last, env_new(arg[2]));
	else
		insert_to_tail(&env->last, env_new(arg[2]));
}
