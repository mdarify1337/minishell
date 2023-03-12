/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:21:55 by mdarify           #+#    #+#             */
/*   Updated: 2023/03/12 14:22:43 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_mlen(char **m)
{
	int	i;

	i = 0;
	if (m && *m)
		while (m[i])
			i++;
	return (i);
}

static int	is_numeric(const char *s)
{
	int	is_numeric;
	int	i;

	is_numeric = 0;
	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] && ft_isdigit(s[i]))
	{
		is_numeric = 1;
		i++;
	}
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] != '\0')
		is_numeric = 0;
	return (is_numeric);
}

long double	ft_atoi_exit(char *str)
{
	int			sign;
	long double	nbr;

	sign = 1;
	nbr = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		nbr = (nbr * 10) + (*str - '0');
		str++;
	}
	return (sign * nbr);
}

int	builtin_exit(char **cmd)
{
	int	size;

	ft_putendl_fd("exit", STDOUT_FILENO);
	size = ft_mlen(cmd);
	if (size == 1)
		exit(fcode.exit_status);
	fcode.exit_status = ft_atoi_exit(cmd[1]);
	if (size == 2)
	{
		if (!is_numeric(cmd[1]) || fcode.exit_status > 2147483647
			|| fcode.exit_status < -2147483648)
		{
			ft_putstr_fd("MINISHELL: exit: ", STDERR_FILENO);
			ft_putstr_fd(cmd[1], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			fcode.exit_status = 255;
			exit(fcode.exit_status);
		}
	}
	if (size == 3)
	{
		ft_putendl_fd("MINISHELL: exit: too many arguments", STDERR_FILENO);
		fcode.exit_status = 1;
	}
	exit(fcode.exit_status);
}

// int	ft_isdigit(int c)
// {
// 	if (c >= 48 && c <= 57)
// 		return (1);
// 	return (0);
// }

// void	check_negative(int *negative, char *str, int *i)
// {
// 	if (str[*i] == '-' || str[*i] == '+')
// 	{
// 		if (str[*i] == '-')
// 			(*negative)++;
// 		(*i)++;
// 	}
// }

// int	get_length(char **args)
// {
// 	int	i;

// 	i = 0;
// 	while (args[i])
// 	i++;
// 	return (i);
// }

// unsigned long long	exit_atoi(char *str, int *negative)
// {
// 	int					i;
// 	unsigned long long	temp;

// 	i = 0;
// 	while (str[i] <= 32)
// 			i++;
// 	check_negative(negative, str, &i);
// 	if (!ft_strcmp(str, "-9223372036854775808") && *negative == 1)
// 		return (9223372036854775808ULL);
// 	temp = 0;
// 	while (str[i])
// 	{
// 		temp = (str[i] - 48) + (temp * 10);
// 		if ((temp > 9223372036854775808ULL && *negative == 1) \
// 		|| !ft_isdigit(str[i]))
// 			return (-1);
// 		if (temp > 9223372036854775807ULL || !ft_isdigit(str[i]))
// 			return (-1);
// 		i++;
// 	}
// 	return (temp);
// }

// void	ft_exit(char **ex)
// {
// 	int			negative;
// 	long long	g;

// 	negative = 0;
// 	g = (long long) exit_atoi(*ex, &negative);
// 	printf("%lld", g);
// 	if (negative == 1 && g != -1)
// 		g *= -1;
// 	if (g != -1 && get_length(ex) > 2)
// 	{
// 		printf("hello\n");
// 		printf("minishell: exit: too many arguments\n");
// 		fcode.exit_status = 1;
// 		return ;
// 	}
// 	else if (g == -1 && ft_strcmp(ex[0], "-1"))
// 	{
// 		printf(">>>>>.hello\n");
// 		printf("minishell: %s\n", ex[0]);
// 		fcode.exit_status = g;
// 		exit(g);
// 	}
// 	fcode.exit_status = g;
// 	exit(fcode.exit_status);
// }