/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:35:41 by mdarify           #+#    #+#             */
/*   Updated: 2023/01/18 20:07:15 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_strlen(char  *s)
{
    int size;

    size = 0;
    while (s[size])
    {
        size++;
    }
    return (size);
}

char    *ft_strcat(char *pdf, char  *s1, char   *s2)
{
    int i;
    int j;
    int m;

    i = 0;
    j = 0;
    m = 0;
    while (s2[i] != '\0')
    {
        pdf[m] = s2[i];
        m++;
        i++;
    }
    while (s1[j] != '\0')
    {
        pdf[m + j] = s1[j];
        j++;
    }
    pdf[m + j] = '\0';
    return (pdf);
}

char    ft_strjoin(char     *s1, char   *s2)
{
    char    *pdf;
    int     size;
    int     len;

    if (!s1)
    {
        s1 = malloc(1);
        *s1 = '\0';
    }
    size = ft_strlen(s1);
    len = ft_strlen(s2) + 1;
    pdf = (char *)malloc((size + len) * sizeof(char));
    if (!pdf)
    {
        return NULL;
        free(pdf);
    }
    pdf = ft_strcat(pdf, s1, s2);
    free(s1);
    return (pdf);
}