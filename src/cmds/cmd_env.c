/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 03:32:12 by hamza             #+#    #+#             */
/*   Updated: 2021/07/15 19:28:33 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_res	cmd_env(t_shell *shell, t_string *args)
{
	int			i;
	t_res		res;
	t_string	output;
	t_env		env;

	(void)args;
	i = -1;
	env = shell->env;
	output = str_dup("");
	while (++i < shell->env.keys.size)
	{
		output = join(output, vector_get(&env.keys, i));
		output = join(output, "=");
		output = join(output, vector_get(&env.values, i));
		output = join(output, "\n");
	}
	res.output = output;
	res.status = TRUE;
	return (res);
}
