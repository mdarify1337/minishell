/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounaji <mmounaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:55:04 by mmounaji          #+#    #+#             */
/*   Updated: 2023/02/28 19:49:50 by mmounaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirection(t_element *elm)
{
	if (!elm)
		return (0);
	if (elm->type == REDIR_IN || elm->type == REDIR_OUT || \
	elm->type == HERE_DOC || elm->type == DREDIR_OUT)
		return (1);
	return (0);
}

t_element	*skip_space(t_element *elm, int flag)
{
	while (elm != NULL && elm->type == WHITE_SPACE)
	{
		if (flag == 1)
			elm = elm->next;
		else
			elm = elm->previous;
	}
	return (elm);
}

int	check_pipe(t_element *elm)
{
	t_element	*before;
	t_element	*after;

	before = elm->previous;
	after = elm->next;
	if (!before || !after)
		return (0);
	if (is_redirection(before) == 1) //todo: space between pipes
		return (0);
	return (1);
}

int	redir_error(t_element *elm)
{
	t_element	*after;

	after = skip_space(elm->next, 1);
	if (after == NULL || (after->type != WORD && after->type != ENV \
	&& after->type != QOUTE && after->type != DOUBLE_QUOTE))
		return (1);
	return (0);
}

int	check_syntax(t_list *lst)
{
	t_element	*elem;

	elem = lst->first;
	if (check_quotes(lst) == 0)
	{
		perror("minishell: detected unclosed quotes");
		exit(0);
	}	
	while (elem)
	{
		if (elem->type == PIPE_LINE && elem->state == GENERAL \
		&& check_pipe(elem) == 0 )
			perror("minishell: syntax error nearrrrr unexpected token |");
		else if (is_redirection(elem) == 1 && redir_error(elem) == 1)
		{
			perror("minishell: syntax error near unexpected token >");
			exit(1);
		}
		elem = elem->next;
	}
	return (0);
}
