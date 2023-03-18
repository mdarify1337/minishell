/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounaji <mmounaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:41:57 by mdarify           #+#    #+#             */
/*   Updated: 2023/03/17 20:06:41 by mmounaji         ###   ########.fr       */
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

char	*ft_remove_char(char	*str, char c)
{
	char	*str1;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	str1 = calloc(ft_strlen(str), 1);
	if (!str1)
		return (NULL);
	while (*str)
	{
		if (*str != c)
			str1[i++] = *str;
		str++;
	}
	return (str1);
}

void	export_with_join(t_env **env, char *arg, int i, t_env_node *node_)
{
	t_env_node	*node;
	char		*tmp;

	tmp = ft_remove_char(arg, '+');
	node = (*env)->first;
	if (!node)
		insert_to_tail(env, env_new(tmp));
	else if (i != -1 && search_by_key(node, ft_substr(tmp, 0, i - 1)) != NULL)
	{
		node_ = search_by_key(node, ft_substr(tmp, 0, i - 1));
		if (node_)
		{
			free(node_->value);
			node_->value = ft_strjoin_free2(node_->value, \
			ft_substr(arg, i + 1, ft_strlen(arg) - i));
		}	
	}
	else if (search_by_key(node, ft_strdup(tmp)) == NULL)
		insert_to_tail(env, env_new(tmp));
	free(tmp);
}
