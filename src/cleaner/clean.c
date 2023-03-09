/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:25:44 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/04 16:46:35 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lexer_cleaner(t_list *lst)
{
	t_element	*elm;
	t_element	*ptr;

	elm = lst->first;
	ptr = elm;
	while (elm)
	{
		ptr = ptr->next;
		free(elm->content);
		free(elm);
		elm = ptr;
	}
}

void	ft_env_cleaner(t_env_node *lst)
{
	t_env_node	*tmp;
	t_env_node	*tmp2;

	tmp = lst;
	tmp2 = tmp;
	while (tmp)
	{
		tmp2 = tmp2->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = tmp2;
	}
}

void	free_2d_array(char **ar)
{
	char	*tmp;

	tmp = *ar;
	while (*ar)
	{
		ar++;
		free(tmp);
		tmp = *ar;
	}
	free(*ar);
}

void	ft_cmd_cleaner(t_cmd_node *node)
{
	t_cmd_node	*ptr;
	t_cmd_node	*elm;

	ptr = node;
	elm = ptr;
	while (ptr)
	{
		ptr = ptr->next;
		free(elm->args);
		free_2d_array(elm->cmd_);
		free(elm);
		elm = ptr;
	}
	free(elm);
}

void	ft_parsing_cleaner(t_list *lst, t_cmd_node *node, t_env *env)
{
	ft_cmd_cleaner(node);
	ft_lexer_cleaner(lst);
	ft_env_cleaner(env->first);
}