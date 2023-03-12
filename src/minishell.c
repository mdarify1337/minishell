/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 21:07:24 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/12 19:07:19 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	print_element(t_list *list)
// {
// 	t_element	*node;

// 	node = list->first;
// 	while (node)
// 	{
// 	printf("--------------------------------------------------\n");
// 	printf("content:%s    ", node->content);
// 	printf(", len:    %i", node->len);
// 	printf(", state:    %i", node->state);
// 	printf(", token:    %i\n", node->type);
// 	printf("--------------------------------------------------\n");
// 		node = node->next;
// 	}
// }

// void	print_parsing(t_cmd_node *cmd)
// {
// 	t_cmd_node	*node;
// 	node = cmd;
// 	int i = 0;
// 	while (node)
// 	{
// 		printf("command : %s\n", node->args);
// 		printf("arguments :");
// 		while (node->cmd_[i])
// 			printf("-%s-",node->cmd_[i++]);
// 		printf("\nio out : %d\n", node->io_out);
// 		printf("io in : %d\n", node->io_in);
// 		printf("------------------------------------------------\n");
// 		node = node->next;
// 		i = 0;
// 	}
// }
int	ft_readline(char **line)
{
	signal(SIGINT, SIG_IGN);
	*line = readline("minishell$> ");
	signal(SIGINT, SIG_IGN);
	if (!*line)
	{
		printf("exit\n");
		fcode.exit_status = 0;
		exit(fcode.exit_status);
	}
	if (ft_strcmp(*line, "") == -1 || ft_strisspace(*line))
		return (1);
	if (strlen(*line) > 0)
		add_history(*line);
	return (0);
}

void free_cmd(t_cmd_node **cmd)
{
	t_cmd_node *tmp;
	int			i;

	while (*cmd)
	{
		i = 0;
		tmp = (*cmd)->next;
		while ((*cmd) && (*cmd)->cmd_[i])
		{
			free((*cmd)->cmd_[i]);
			i++;
		}
		free((*cmd)->cmd_);
		free((*cmd)->args);
		free(*cmd);
		*cmd = tmp;	
	}
}

void	minishell(char **envv)
{
	char		*line;
	t_list		*element;
	t_env		*env;
	t_command	*cmd;

	line = NULL;
	env = ft_init_env(envv);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		if (ft_readline(&line))
		{
			free(line);
			continue ;
		}
		element = lexer(line);
		execute_here_doc(&element);
		check_syntax(element);
		ft_expand(&element, env);
		cmd = parse_command(&element);
		ft_split_args(&cmd->first);
		ft_execution_command(cmd->first, env);
		ft_parsing_cleaner(element, cmd->first, env);
		free(cmd);
		// free_cmd(&cmd->first);
	}
}
