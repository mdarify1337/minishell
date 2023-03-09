/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 21:07:24 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/07 09:56:07 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_element(t_list *list)
{
	t_element	*node;

	node = list->first;
	while (node)
	{
	printf("--------------------------------------------------\n");
	printf("content:%s    ", node->content);
	printf(", len:    %i", node->len);
	printf(", state:    %i", node->state);
	printf(", token:    %i\n", node->type);
	printf("--------------------------------------------------\n");
		node = node->next;
	}
}

void	print_parsing(t_cmd_node *cmd)
{
	t_cmd_node *node;
	node = cmd;
	int i = 0;
	if (!node || !node->args || !node->cmd_ )
		return;
	while (node)
	{
		printf("command : %s\n", node->args);
		printf("arguments :");
		
		while (node->cmd_[i])
			printf("-%s-",node->cmd_[i++]);
		printf("\nio out : %d\n", node->io_out);
		printf("io in : %d\n", node->io_in);
		printf("------------------------------------------------\n");
		node = node->next;
		i = 0;
	}
}
int	ft_readline(char **line)
{
	*line = readline("minishell_1337$> ");
	if (!*line)
	{
		printf("exit\n");
		exit(1);
	}
	if (ft_strcmp(*line, "") == 0 || ft_strisspace(*line))
		return (1);
	if (ft_strlen(*line) > 0)
		add_history(*line);
	return (0);
}

void print_env(t_env *envv)
{
	t_env_node *env;
	
	env = envv->first;
	while (env)
	{
		printf ("<< %s\n", env->value);
		env = env->next;
	}
}

void	minishell(char **envv)
{
	char	*line;
	t_list	*element;
	t_env	*env;
	t_cmd_node	*cmd;
	

	cmd = NULL;
	line = NULL;
	// command = NULL;
	env = ft_init_env(envv);
	// fcode.new_env = env;
	init_signals();
	while (1)
	{
		if (ft_readline(&line))
		{
			free(line);
			continue ;
		}
		element = lexer(line);
		check_syntax(element);
		// todo; continue when syntax error
		execute_here_doc(&element);
		ft_expand(&element, env);
		cmd = parse_command(&element);
		ft_split_args(&cmd);
		// print_env(env);
		// print_parsing(cmd);
		// print_element(element);
		//printf("********%s\n", cmd->args);
		// fcheck_execv_builtin(cmd, env);
		// cmd->env = env;
		ft_execution_command(cmd, env);
		// env = cmd->env;
	}
}
