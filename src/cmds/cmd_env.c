/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 03:32:12 by hamza             #+#    #+#             */
/*   Updated: 2021/09/24 00:43:59 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_res	cmd_env(t_shell *shell, T_STRING *args, int n)
{
	int			i;
	t_res		res;
	T_STRING	output;
	t_env		env;

	(void)args;
	(void)n;
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
