/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 18:37:34 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/04 16:49:31 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_pipe(t_element *elm)
{
	while (elm)
	{
		if (elm->type == PIPE_LINE)
			return (1);
		elm = elm->next;
	}
	return (0);
}	

void	update_redirection(t_cmd_node *cmd, t_element *elm)
{
	if (elm->type == REDIR_IN || elm->type == HERE_DOC)
	{
		cmd->io_in = open(elm->next->content, O_RDONLY , 0644);
		if (cmd->io_in == -1)
			perror("open failed");
	}
	else if (elm->type == REDIR_OUT)
	{
		cmd->io_out = open(elm->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->io_out == -1)
			perror("open failed");
	}
	else if (elm->type == DREDIR_OUT)
	{
		cmd->io_out = open(elm->next->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->io_out == -1)
			perror("open failed");
	}
}
//TODO: add ft_strcat leaks strcpy

char	*ft_realloc(char *old, char *new)
{
	char	*p;

	if (!old)
	{
		old = ft_strdup(new);
		old = ft_strjoin(old, " ");
		return (old);
	}
	p = (char *)malloc(strlen(old) + strlen(new) + 1);
	if (p)
	{
		strcpy(p, old);
		strcat(p, new);
		p = ft_strjoin(p, " ");
	}
	free(old);
	return (p);
}

void	ft_cmdadd_back(t_cmd_node **lst, t_cmd_node *new)
{
	t_cmd_node	*tmp;

	tmp = *lst;
	if (lst == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}
