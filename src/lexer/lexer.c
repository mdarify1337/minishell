/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounaji <mmounaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:58:12 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/17 21:39:08 by mmounaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tokenizer(t_list *tokens, char *line, int i, enum e_state state)
{
	if (line[i] == '>' || line[i] == '<')
		i += tokenize_redir(tokens, line, i, state);
	else if (in_charset(line[i]) == 0)
		i += get_word(tokens, line + i, state);
	else if (ft_isspace(line[i]) && state != GENERAL)
		ft_lstadd_back(&tokens, ft_lstnew(line + (i++), 1, WHITE_SPACE, state));
	else if (ft_isspace(line[i]))
		ft_lstadd_back(&tokens, ft_lstnew(line + (i++), 1, GEN_WS, state));
	else if (line[i] == '|')
		ft_lstadd_back(&tokens, ft_lstnew(line + (i++), 1, PIPE_LINE, state));
	else if (line[i] == '$')
	{
		if (in_charset(line[i + 1]) || line[i + 1] == '=')
			ft_lstadd_back(&tokens, ft_lstnew(line + (i++), 1, WORD, state));
		else
			i += get_env_var(tokens, line + i, state);
	}
	else
		i++;
	return (i);
}

t_list	*lexer(char *line, int i)
{
	t_list			*tokens;
	enum e_state	state;

	state = GENERAL;
	tokens = NULL;
	tokens = init_tokens(tokens);
	while (line[i])
	{
		if (line[i] == '\'' )
		{
			if (line[i + 1] == '\'')
				ft_lstadd_back(&tokens, ft_lstnew("", 1, WORD, IN_QUOTE));
			quotes_state(tokens, line + (i++), &state, QOUTE);
		}
		else if (line[i] == '\"')
		{
			if (line[i + 1] == '\"')
				ft_lstadd_back(&tokens, ft_lstnew("", 1, WORD, IN_DQUOTE));
			quotes_state(tokens, line + (i++), &state, DOUBLE_QUOTE);
		}
		else
			i = tokenizer(tokens, line, i, state);
	}
	free(line);
	return (tokens);
}
