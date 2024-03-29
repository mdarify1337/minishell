/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounaji <mmounaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 21:07:24 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/17 21:07:50 by mmounaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_ctlc(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &t);
}

int	ft_readline(char **line)
{
	signal(SIGINT, &sig_handler);
	*line = readline("minishell$> ");
	signal(SIGINT, SIG_IGN);
	if (!(*line))
	{
		write(2, "exit\n", 5);
		exit (g_fcode.exit_status);
	}
	if (ft_strcmp(*line, "") == -1 || ft_strisspace(*line))
		return (1);
	if (strlen(*line) > 0)
		add_history(*line);
	return (0);
}

void	free_cmd(t_cmd_node **cmd)
{
	t_cmd_node	*tmp;
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

void	fminishell_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sig_handler);
	remove_ctlc();
}

void	minishell(char **envp)
{
	char		*line;
	t_list		*element;
	t_env		*env;
	t_command	*cmd;

	line = NULL;
	env = ft_init_env(envp);
	fminishell_signal();
	while (1)
	{
		if (ft_readline(&line))
		{
			free(line);
			continue ;
		}
		element = lexer(line, 0);
		execute_here_doc(&element);
		if (check_syntax(element) == 0)
			continue ;
		ft_expand(&element, env);
		cmd = parse_command(&element);
		ft_split_args(&cmd->first);
		ft_execution_command(cmd->first, env);
		ft_parsing_cleaner(element, cmd->first, cmd);
	}
}
