/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounaji <mmounaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:21:59 by mdarify           #+#    #+#             */
/*   Updated: 2023/03/17 16:29:39 by mmounaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_element	*skip_space(t_element *elm, int flag)
{
	while (elm != NULL && (elm->type == WHITE_SPACE || elm->type == GEN_WS))
	{
		if (flag == 1)
			elm = elm->next;
		else
			elm = elm->previous;
	}
	return (elm);
}

void	ft_check(int fd, char *filename, int flag)
{
	if (fd == -1 && flag)
	{
		ft_putstr_fd("minishell :", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
		g_fcode.exit_status = 1;
	}
	else if (fd == -1)
	{
		ft_putstr_fd("minishell :", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(" : Permission denied\n", 2);
		g_fcode.exit_status = 1;
	}
}
