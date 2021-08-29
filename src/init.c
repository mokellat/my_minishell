/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:14:37 by hmellahi          #+#    #+#             */
/*   Updated: 2021/07/15 19:27:35 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_string	get_env(t_shell *shell, t_string var_key)
{
	t_string	value;
	int			index;

	index = vector_find(&shell->env.keys, var_key);
	if (index == -1)
		return (NULL);
	value = vector_get(&shell->env.values, index);
	return (value);
}

void	init_env(t_env *env, t_string *env_vars)
{
	int			i;
	t_string	key;
	t_string	value;
	t_string	ptr;

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

void	init_shell(t_shell *shell, t_string *env_vars)
{
	shell->cmds_str = init_cmds_str();
	shell->cmds = &cmds;
	shell->status_code = 0;
	shell->in_heredoc = 0;
	cmd_pwd(shell, NULL);
	init_env(&shell->env, env_vars);
	shell->depth = 1;
	init_signals();
}
