/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 15:28:53 by hmellahi          #+#    #+#             */
/*   Updated: 2021/07/14 15:41:26 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_special_chars(const char *str, int i, int *neg)
{
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*neg *= -1;
		i++;
	}
	return (i);
}

int	spec_atoi(const char *str)
{
	int					neg;
	int					i;
	unsigned long long	num;
	unsigned long long	a;

	i = 0;
	neg = 1;
	num = 0;
	check_special_chars(str, i, &neg);
	a = __LONG_MAX__ / 10;
	while (str[i] >= 48 && str[i] <= 57)
	{
		if ((num > a) || ((str[i] > '7' && neg == 1)
				|| (str[i] > '8' && neg == -1)))
			return (-1);
		num = num * 10 + (str[i] - 48);
		i++;
	}
	num %= 256;
	if (neg == -1)
		num = 256 - num;
	return (num % 256);
}

int	str_is_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] >= '0' && str[i] <= '9')
			return (1);
	return (0);
}

t_res	exit_with_empty_res(t_shell *shell, int error)
{
	t_res	res;

	if (error == NUM_ARG_REQ)
		res.status = FALSE;
	else
		res.status = TRUE;
	res.output = "";
	shell->exit_code = print_err("exit", NUM_ARG_REQ);
	return (res);
}

t_res	cmd_exit(t_shell *shell, t_string *args)
{
	t_res	res;

	res.status = FALSE;
	res.output = "";
	if (tablen(args) >= 2 && !str_is_digit(args[1]))
		return (exit_with_empty_res(shell, NUM_ARG_REQ));
	if (tablen(args) == 2)
	{
		shell->exit_code = spec_atoi(args[1]);
		if (shell->exit_code == -1)
			return (exit_with_empty_res(shell, NUM_ARG_REQ));
	}
	else if (tablen(args) > 2)
		return (exit_with_empty_res(shell, TOO_MANY_ARGS));
	return (res);
}
