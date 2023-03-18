/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounaji <mmounaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:56:49 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/17 22:27:18 by mmounaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_valid_quotes(t_element *elm)
{
	if ((elm->type == QOUTE && elm->state == IN_DQUOTE) || (elm->type \
	== DOUBLE_QUOTE && elm->state == IN_QUOTE))
		return (1);
	return (0);
}

t_cmd_node	*cmd_new(void)
{
	t_cmd_node	*cmd;

	cmd = calloc(sizeof(t_cmd_node), 1);
	if (!cmd)
		return (NULL);
	cmd->io_in = STDIN_FILE;
	cmd->io_out = STDOUT_FILE;
	cmd->cmd_ = calloc(sizeof(char *), 1);
	return (cmd);
}

void	ft_split_args(t_cmd_node **args)
{
	t_cmd_node	*cmd;

	cmd = *args;
	if (!cmd)
		return ;
	while (cmd)
	{
		if (cmd->args != NULL)
		{
			free(cmd->cmd_);
			cmd->cmd_ = ft_split(cmd->args, '*');
			free(cmd->args);
			cmd->args = ft_strdup(cmd->cmd_[0]);
		}
		cmd = cmd->next;
	}
}

void	parse_coman2(t_element **elm, t_cmd_node **tmp, t_command **cmd)
{
	if ((*elm)->type == PIPE_LINE && (*elm)->state == GENERAL)
	{
		ft_cmdadd_back(cmd, (*tmp));
		(*tmp) = cmd_new();
	}
	else if (((*elm)->type != QOUTE && (*elm)->type != DOUBLE_QUOTE \
	&& (*elm)->type != GEN_WS) \
	|| ((*elm)->state == IN_DQUOTE || (*elm)->state == IN_QUOTE))
	{
		if ((*elm)->next && (*elm)->next->type != GEN_WS)
		{	
			while ((*elm) && (*elm)->type != QOUTE && \
			(*elm)->type != DOUBLE_QUOTE && (*elm)->type != GEN_WS)
			{
				(*tmp)->args = ft_strjoin_free((*tmp)->args, (*elm)->content);
				(*elm) = (*elm)->next;
			}
		}
		else
			(*tmp)->args = ft_realloc((*tmp)->args, \
			(*elm)->content, (*elm)->next);
	}
}

t_command	*parse_command(t_list **list)
{
	t_command		*cmd;
	t_cmd_node		*tmp;
	t_element		*elm;

	if (!list)
		return (NULL);
	elm = (*list)->first;
	cmd = calloc(1, sizeof(t_command));
	tmp = cmd_new();
	while (elm)
	{
		if (is_redirection(elm))
		{
			update_redirection(tmp, elm);
			while (elm && elm->type != WORD && elm->type != ENV)
				elm = elm->next;
		}
		else
			parse_coman2(&elm, &tmp, &cmd);
		if (elm)
			elm = elm->next;
	}
	ft_cmdadd_back(&cmd, tmp);
	return (cmd);
}
