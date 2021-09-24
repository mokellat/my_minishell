/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:14:37 by hmellahi          #+#    #+#             */
/*   Updated: 2021/09/24 01:59:07 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

T_STRING	get_env(t_shell *shell, T_STRING var_key)
{
	T_STRING	value;
	int			index;

	index = vector_find(&shell->env.keys, var_key);
	if (index == -1)
		return (NULL);
	value = vector_get(&shell->env.values, index);
	return (value);
}

void	init_env(t_env *env, T_STRING *env_vars)
{
	int			i;
	T_STRING	key;
	T_STRING	value;
	T_STRING	ptr;

	new_vector(&env->keys);
	new_vector(&env->values);
	i = -1;
	while (env_vars[++i])
	{
		ptr = char_addr('=', env_vars[i]);
		key = cpy_from_to(env_vars[i], ptr);
		value = ptr + 1;
		if (str_cmp("SHLVL", key))
			value = ft_itoa(atoi(value) + 1);
		vector_push_back(&env->keys, key);
		vector_push_back(&env->values, value);
	}
}

void	init_shell(t_shell *shell, T_STRING *env_vars)
{
	shell->cmds_str = init_cmds_str();
	shell->cmds = &cmds;
	shell->status_code = 0;
	shell->in_heredoc = 0;
	shell->is_exit_printed = 0;
	cmd_pwd(shell, NULL, 0);
	init_env(&shell->env, env_vars);
	shell->depth = 1;
	init_signals();
}
