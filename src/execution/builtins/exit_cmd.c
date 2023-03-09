/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:21:55 by mdarify           #+#    #+#             */
/*   Updated: 2023/03/04 12:07:07 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

void	check_negative(int *negative, char *str, int *i)
{
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			(*negative)++;
		(*i)++;
	}
}

int	get_length(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	i++;
	return (i);
}

unsigned long long	exit_atoi(char *str, int *negative)
{
	int					i;
	unsigned long long	temp;

	i = 0;
	while (str[i] <= 32)
			i++;
	check_negative(negative, str, &i);
	if (!ft_strcmp(str, "-9223372036854775808") && *negative == 1)
		return (9223372036854775808ULL);
	temp = 0;
	while (str[i])
	{
		temp = (str[i] - 48) + (temp * 10);
		if ((temp > 9223372036854775808ULL && *negative == 1) \
		|| !ft_isdigit(str[i]))
			return (-1);
		if (temp > 9223372036854775807ULL || !ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (temp);
}

void	ft_exit(char **ex)
{
	int			negative;
	long long	g;

	negative = 0;
	g = (long long) exit_atoi(*ex, &negative);
	if (negative == 1 && g != -1)
		g *= -1;
	if (g != -1 && get_length(ex) != 1)
	{
		printf("minishell: exit: too many arguments\n");
		fcode.exit_status = 1;
		return ;
	} 
	else if (g == -1 && ft_strcmp(ex[0], "-1"))
	{
		printf("minishell: exit: %s\n", ex[0]);
		fcode.exit_status = 0;
		exit(0);
	}
	fcode.exit_status = g;
	exit(fcode.exit_status);
}