/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:58:12 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/04 16:47:21 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	tokenize(t_element *tokens, char *line, int i, enum e_state *state)
// {
// 	if (in_charset(line[i]) == 0)
// 	{
// 		printf("no null");
// 		i += get_word(tokens, line + i, *state);
// 	}
// 	return (i);
// }

t_list	*lexer(char *line)
{
	int				i;
	t_list			*tokens;
	enum e_state	state;

	i = 0;
	state = GENERAL;
	tokens = NULL;
	tokens = init_tokens(tokens);
	while (line[i])
	{
		if (in_charset(line[i]) == 0)
		{
			i += get_word(tokens, line + i, state);
		}
		else if (line[i] == '$')
		{
			if (in_charset(line[i + 1]) || line[i + 1] == '=')
			{
				ft_lstadd_back(&tokens, ft_lstnew(line + i, 1, WORD, state));
				i++;
			}
			else
			i += get_env_var(tokens, line + i, state);
		}
		else if (line[i] == '>' || line[i] == '<')
			i += tokenize_redir(tokens, line, i, &state);
		else if (line[i] == '|')
			ft_lstadd_back(&tokens, ft_lstnew(line + (i++), 1, PIPE_LINE, state));
		else if (line[i] == '\'')
			quotes_state(tokens, line + (i++), &state, QOUTE);
		else if (line[i] == '\"')
			quotes_state(tokens, line + (i++), &state, DOUBLE_QUOTE);
		else if (ft_isspace(line[i]) && state != GENERAL)
			ft_lstadd_back(&tokens, ft_lstnew(line + (i++), 1, WHITE_SPACE, state));
		else
			i++;
	}
	free(line);
	return (tokens);
}
