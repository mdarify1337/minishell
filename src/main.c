/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounaji <mmounaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:21:17 by mmounaji          #+#    #+#             */
/*   Updated: 2023/02/14 12:11:47 by mmounaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)av;
	if (ac != 1 || !*env)
		return (1);
	minishell(env);
	return (0);
}