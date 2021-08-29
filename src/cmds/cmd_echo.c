/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:18:05 by hmellahi          #+#    #+#             */
/*   Updated: 2021/07/15 19:28:33 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	look_for_flags(t_shell *shell, t_string *args)
{
	int			i;
	t_string	flag;

	i = 1;
	shell->print_nl = TRUE;
	while (args[i])
	{
		flag = sub_str(args[i], 0, 2);
		if (!str_cmp(flag, "-n"))
			break ;
		shell->print_nl = FALSE;
		i++;
	}
	return (i);
}

t_res	cmd_echo(t_shell *shell, t_string *args)
{
	t_res		res;
	int			i;
	int			j;

	i = look_for_flags(shell, args);
	j = i;
	res.output = "";
	while (args[i])
	{
		res.output = join(res.output, args[i]);
		if (j != 0 && args[i + 1])
			res.output = join(res.output, " ");
		i++;
	}
	if (shell->print_nl == TRUE)
		res.output = join(res.output, "\n");
	res.status = TRUE;
	shell->exit_code = 0;
	return (res);
}
