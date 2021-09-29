/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:31:44 by hmellahi          #+#    #+#             */
/*   Updated: 2021/09/29 11:55:10 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

T_STRING	*bubble_sort(T_STRING *arr, int n)
{
	int	i;
	int	j;

	i = -1;
	while (++i < n - 1)
	{
		j = -1;
		while (++j < n - i - 1)
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
				swap(&arr[j], &arr[j + 1]);
	}
	return (arr);
}

t_env	env_cpy(t_env env)
{
	t_env	cpy;

	cpy.keys = *vector_cpy(&env.keys);
	cpy.values = *vector_cpy(&env.values);
	return (cpy);
}

t_res	show_env_list_sorted(t_env old)
{
	int			i;
	T_STRING	*arr;
	t_res		res;

	i = -1;
	arr = env_to_arr(&old, TRUE);
	arr = bubble_sort(arr, old.keys.size);
	res.output = "";
	res.status = TRUE;
	while (++i < old.keys.size)
	{
		res.output = join(res.output, "declare -x ");
		res.output = join(res.output, arr[i]);
		res.output = join(res.output, "\n");
	}
	return (res);
}

int	update_env_var(t_shell *shell, T_STRING key, T_STRING value, T_STRING arg)
{
	int			index;
	T_STRING	error;

	error = validate_identifier(arg, "export");
	if (*error != EMPTY)
	{
		shell->exit_code = print_err(error, NOT_VALID_IDENT);
		return (-1);
	}
	index = vector_find(&shell->env.keys, key);
	if (index == -1)
	{
		vector_push_back(&shell->env.keys, key);
		vector_push_back(&shell->env.values, value);
	}
	else if (value)
		vector_set(&shell->env.values, index, value);
	return (0);
}

t_res	cmd_export(t_shell *shell, T_STRING *args, int n)
{
	t_res		res;
	int			i;
	T_STRING	key;
	T_STRING	value;

	i = 0;
	res.output = "";
	res.status = TRUE;
	shell->exit_code = 0;
	if (n == 1)
		return (show_env_list_sorted(shell->env));
	while (++i < n)
	{
		value = char_addr('=', args[i]);
		if (value == NULL)
			key = args[i];
		else
			key = cpy_from_to(args[i], value++);
		if (update_env_var(shell, key, value, args[i]) == -1)
			continue ;
	}
	return (res);
}
