/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounaji <mmounaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:55:04 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/17 21:39:22 by mmounaji         ###   ########.fr       */
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

int	check_pipe(t_element *elm)
{
	t_element	*before;
	t_element	*after;

	before = elm->previous;
	after = elm->next;
	if (!before || !after)
		return (0);
	if (is_redirection(before) == 1 || before->type == PIPE_LINE || \
	after->type == PIPE_LINE)
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

int	main_check(t_element *elem)
{
	while (elem)
	{
		if (elem->type == PIPE_LINE && elem->state == GENERAL \
			&& check_pipe(elem) == 0)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token |\n", 2);
			g_fcode.exit_status = 258;
			return (0);
		}	
		else if (is_redirection(elem) == 1 && redir_error(elem) == 1)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token >\n", 2);
			g_fcode.exit_status = 1;
			return (0);
		}
		elem = elem->next;
	}
	return (1);
}

int	check_syntax(t_list *lst)
{
	t_element	*elem;

	elem = lst->first;
	if (check_quotes(lst) == 0)
	{
		ft_putstr_fd("minishell: detected unclosed quotes", 2);
		g_fcode.exit_status = 0;
		return (0);
	}	
	if (main_check(elem) == 0)
		return (0);
	return (1);
}
