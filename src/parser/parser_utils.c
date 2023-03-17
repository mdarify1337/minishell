/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 18:37:34 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/17 10:23:24 by mdarify          ###   ########.fr       */
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
	t_element	*tmp;

	tmp = elm;
	while (tmp && tmp->type != WORD && tmp->type != ENV)
		tmp = tmp->next;
	if (!tmp)
		return ;
	if (cmd->io_in != -1 && cmd->io_out != -1 && (elm->type == REDIR_IN
			|| elm->type == HERE_DOC))
	{
		cmd->io_in = open(tmp->content, O_RDONLY, 0644);
		ft_check(cmd->io_in, tmp->content, 1);
	}
	else if (cmd->io_in != -1 && cmd->io_out != -1 && elm->type == REDIR_OUT)
	{
		cmd->io_out = open(tmp->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		ft_check(cmd->io_out, tmp->content, 0);
	}
	else if (cmd->io_in != -1 && cmd->io_out != -1 && elm->type == DREDIR_OUT)
	{
		cmd->io_out = open(tmp->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		ft_check(cmd->io_out, tmp->content, 0);
	}
}

char	*ft_strcat(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = calloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}	
	while (s2[j])
		str[i++] = s2[j++];
	free(s1);
	return (str);
}

char	*ft_realloc(char *old, char *new, t_element *next)
{
	if (ft_isspace(new[0]) == 1)
	{
		old = ft_strjoin_free(old, " ");
		return (old);
	}
	if (!old)
	{
		old = ft_strdup(new);
		if ((next && next->type != WHITE_SPACE)
			|| (next && next->state == GENERAL))
			old = ft_strjoin_free(old, "*");
		return (old);
	}
	old = ft_strcat(old, new);
	if ((next && next->type != WHITE_SPACE) || (next && next->state == GENERAL))
		old = ft_strjoin_free(old, "*");
	return (old);
}

void	ft_cmdadd_back(t_command **list, t_cmd_node *new)
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
