/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:56:49 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/07 13:30:10 by mdarify          ###   ########.fr       */
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
	cmd->args = NULL;
	cmd->cmd_ = calloc(sizeof(char *), 1);
	cmd->next = NULL;
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
			cmd->cmd_ = ft_split(cmd->args, ' ');
			free(cmd->args);
			cmd->args = ft_strdup(cmd->cmd_[0]);
		}
		cmd = cmd->next;
	}
}

t_cmd_node	*parse_command(t_list **list)
{
	t_cmd_node		*cmd;
	t_cmd_node		*tmp;
	t_element		*elm;

	if (!list)
		return (NULL);
	elm = (*list)->first;
	cmd = NULL;
	tmp = cmd_new();
	while (elm)
	{
		if (is_redirection(elm))
		{
			update_redirection(tmp, elm);
			elm = elm->next;
		}
		else if (elm->type == PIPE_LINE)
		{
			ft_cmdadd_back(&cmd, tmp);
			tmp = cmd_new();
		}
		else if ((elm->type != QOUTE && elm->type != DOUBLE_QUOTE) || \
		check_valid_quotes(elm))
			tmp->args = ft_realloc(tmp->args, elm->content);
		elm = elm->next;
	}
	if (!cmd)
		return (tmp);
	else
		ft_cmdadd_back(&cmd, tmp);
	return (cmd);
}

//add type to check if node is command or pipe