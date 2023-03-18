/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounaji <mmounaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:38:23 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/17 19:50:26 by mmounaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**convert_array(t_env *env)
{
	t_env_node	*tmp;
	char		**arr;
	int			i;
	int			size;

	i = 0;
	tmp = env->first;
	size = ft_lstsize(tmp);
	arr = calloc(size + 1, sizeof(char *));
	if (arr)
	{
		while (i < size)
		{
			arr[i] = ft_strdup(tmp->key);
			if (tmp->value)
			{
				arr[i] = ft_strjoin_free(arr[i], "=");
				arr[i] = ft_strjoin_free(arr[i], tmp->value);
			}
			tmp = tmp->next;
			i++;
		}
		arr[i] = NULL;
	}
	return (arr);
}

t_env_node	*search_by_key(t_env_node *head, char *key)
{
	t_env_node	*tmp;

	tmp = head;
	if (!head)
	{
		free(key);
		return (NULL);
	}	
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(key);
			return (tmp);
		}
		tmp = tmp->next;
	}
	free(key);
	return (NULL);
}

void	insert_to_tail(t_env **env, t_env_node *new)
{
	t_env_node	*tmp;

	if (!new)
		return ;
	tmp = (*env)->first;
	if (!(*env)->first)
	{
		(*env)->first = new;
		(*env)->first->previous = NULL;
	}	
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->previous = tmp;
	}
}
