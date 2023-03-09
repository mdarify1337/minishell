/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounaji <mmounaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:13:54 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/01 21:23:01 by mmounaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strndup(char *s1, int n)
{
	char	*copy;
	size_t	s1_len;
	int		i;

	i = 0;
	s1_len = strlen(s1);
	copy = malloc(sizeof(char) * (s1_len + 1));
	if (!copy)
		return (NULL);
	while (s1[i] && i < n)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

int	ft_lstsize(t_env_node *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

t_list	*init_tokens(t_list *list)
{
	list = calloc(sizeof(t_list), 1);
	if (!list)
		return (NULL);
	return (list);
}

t_element	*ft_lstnew(char *content, int len, enum e_token type, \
enum e_state state)
{
	t_element	*node;

	node = (t_element *)malloc(sizeof(t_element));
	if (!node)
		return (NULL);
	node->content = ft_strndup(content, len);
	node->len = len;
	node->type = type;
	node->state = state;
	node->next = NULL;
	node->previous = NULL;
	return (node);
}

void	ft_lstfree(t_element *list)
{
	free(list->content);
	free(list);
}

void	ft_lstadd_back(t_list **list, t_element *new)
{
	if ((*list)->first == NULL)
		(*list)->first = new;
	else
	{
		(*list)->last->next = new;
		new->previous = (*list)->last;
	}
	(*list)->last = new;
}
//switching from simple to double list at env struct