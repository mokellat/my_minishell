/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:18:05 by hmellahi          #+#    #+#             */
/*   Updated: 2021/09/20 18:46:55 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	look_for_flags(t_shell *shell, T_STRING *args, int n)
{
	int			i;
	T_STRING	flag;

	i = 1;
	shell->print_nl = TRUE;
	while (i < n)
	{
		flag = sub_str(args[i], 0, 2);
		if (!str_cmp(flag, "-n"))
			break ;
		shell->print_nl = FALSE;
		i++;
	}
	return (i);
}

t_res	cmd_echo(t_shell *shell, T_STRING *args, int n)
{
	t_res		res;
	int			i;
	int			j;

	i = look_for_flags(shell, args, n);
	j = i;
	res.output = "";
	while (i < n)
	{
		res.output = join(res.output, args[i]);
		if (j != 0 && (i + 1) < n && args[i + 1])
			res.output = join(res.output, " ");
		i++;
	}
	if (shell->print_nl == TRUE)
		res.output = join(res.output, "\n");
	res.status = TRUE;
	shell->exit_code = 0;
	return (res);
}
