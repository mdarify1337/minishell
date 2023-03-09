/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:02:26 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/02 13:42:09 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	env_cmd(t_env	*env)
{
	t_env_node	*node;

	node = env->first;
	while (node)
	{
		if (node->value != NULL)
			printf("%s=%s\n", node->key, node->value);
		node = node->next;
	}
	return (1);
}
