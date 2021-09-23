/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:16:12 by hmellahi          #+#    #+#             */
/*   Updated: 2021/09/23 19:46:00 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

T_STRING	validate_identifier(T_STRING ident, T_STRING cmd)
{
	T_STRING	msg;

	msg = "";
	if (!ft_isalpha(ident[0]))
	{
		msg = join(cmd, ": `");
		msg = join(msg, ident);
		msg = join(msg, "': ");
	}
	return (msg);
}

void	delete_env_var(t_shell *shell, int index)
{
	vector_delete(&shell->env.keys, index);
	vector_delete(&shell->env.values, index);
}

t_res	cmd_unset(t_shell *shell, T_STRING *args, int n)
{
	t_res		res;
	int			i;
	T_STRING	key;
	int			index;
	T_STRING	error;

	i = 0;
	res.output = "";
	while (++i < n)
	{
		key = args[i];
		error = validate_identifier(key, "unset");
		if (*error != EMPTY)
		{
			shell->exit_code = print_err(error, NOT_VALID_IDENT);
			continue ;
		}
		index = vector_find(&shell->env.keys, key);
		if (index != -1)
			delete_env_var(shell, index);
	}
	res.status = TRUE;
	return (res);
}
