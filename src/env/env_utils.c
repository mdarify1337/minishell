/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounaji <mmounaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:56:09 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/17 11:43:37 by mmounaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_free(t_env_node *lst)
{
	free(lst->key);
	free(lst->value);
	free(lst);
}

int	check_key(char *key)
{
	while (*key)
	{
		if (!ft_is_alpha(*key))
			return (0);
		key++;
	}
	return (1);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*res;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	if ((size_t)len >= ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	i = start;
	j = 0;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (0);
	while (s[i] && j < len)
	{
		res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}
