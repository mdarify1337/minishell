/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:03:39 by mdarify           #+#    #+#             */
/*   Updated: 2023/03/17 10:21:02 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*resulttab;
	size_t	size;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	resulttab = malloc(sizeof(char) * (size + 1));
	if (!resulttab)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		resulttab[i++] = s1[j++];
	j = 0;
	while (s2[j])
		resulttab[i++] = s2[j++];
	resulttab[i] = '\0';
	return (resulttab);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*resulttab;
	size_t	size;
	size_t	i;
	size_t	j;

	if (!s1)
		return (ft_strdup(s2));
	size = ft_strlen(s1) + ft_strlen(s2);
	resulttab = malloc(sizeof(char) * (size + 1));
	if (!resulttab)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		resulttab[i++] = s1[j++];
	j = 0;
	while (s2[j])
		resulttab[i++] = s2[j++];
	resulttab[i] = '\0';
	free(s1);
	return (resulttab);
}

char	*ft_strjoin_free2(char *s1, char *s2)
{
	char	*resulttab;
	size_t	size;
	size_t	i;
	size_t	j;

	size = ft_strlen(s1) + ft_strlen(s2);
	resulttab = malloc(sizeof(char) * (size + 1));
	if (!resulttab)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		resulttab[i++] = s1[j++];
	j = 0;
	while (s2[j])
		resulttab[i++] = s2[j++];
	resulttab[i] = '\0';
	free(s2);
	return (resulttab);
}
