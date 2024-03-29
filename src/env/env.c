/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounaji <mmounaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:55:59 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/17 21:39:58 by mmounaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_node	*key_error(char	*env, char *s1, char *s2)
{
	free(s1);
	free(s2);
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd(env, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	g_fcode.exit_status = 1;
	return (NULL);
}

t_env_node	*env_new(char *env)
{
	char		*key;
	t_env_node	*lst;
	char		*value;
	int			pos;

	lst = calloc(sizeof(t_env_node), 1);
	pos = ft_strchr(env, '=');
	if (pos == -1)
	{
		value = NULL;
		key = ft_strdup(env);
	}
	else
	{
		key = ft_substr(env, 0, pos);
		value = ft_substr(env, pos + 1, ft_strlen(env) - pos);
		if (!value || !key)
			return (NULL);
	}
	if (!check_key(key))
		return (key_error(env, key, value));
	lst->key = key;
	lst->value = value;
	return (lst);
}

void	add_env(t_env **env_list, t_env_node *node)
{
	if (!node)
		return ;
	if ((*env_list) && (*env_list)->first == NULL)
		(*env_list)->first = node;
	else
	{
		(*env_list)->last->next = node;
		node->previous = (*env_list)->last;
	}
	(*env_list)->last = node;
}

t_env	*ft_init_env(char **env)
{
	t_env	*lst;
	int		i;

	lst = calloc(sizeof(t_env), 1);
	i = -1;
	while (env[++i])
	{
		add_env(&lst, env_new(env[i]));
	}	
	return (lst);
}
