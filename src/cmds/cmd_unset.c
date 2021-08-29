/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:16:12 by hmellahi          #+#    #+#             */
/*   Updated: 2021/07/15 19:28:33 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_string	validate_identifier(t_string ident, t_string cmd)
{
	t_string	msg;

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

t_res	cmd_unset(t_shell *shell, t_string *args)
{
	t_res		res;
	int			i;
	t_string	key;
	int			index;
	t_string	error;

	i = 0;
	res.output = "";
	while (args[++i])
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
