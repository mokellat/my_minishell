/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:59:06 by hmellahi          #+#    #+#             */
/*   Updated: 2021/09/25 16:17:45 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_var_value(T_STRING s, T_STRING *expanded_str, int *i, T_STRING *buff)
{
	T_STRING	val;

	if (!s[*i])
	{
		*expanded_str = join(*expanded_str, "$");
		return (1);
	}
	if (is_digit(s[*i]) && (*i)++)
		return (2);
	if (s[*i] == '?' && (*i)++)
	{
		*expanded_str = join(*expanded_str,
				ft_itoa(shell_ref(NULL)->exit_code));
		return (2);
	}
	while (*i < (str_len(s))
		&& (ft_isalpha(s[*i]) || s[*i] == '_' || is_digit(s[*i])))
		*buff = join_c(*buff, s[(*i)++]);
	val = get_env(shell_ref(NULL), *buff);
	val && (*expanded_str = join(*expanded_str, val));
	return (0);
}

void	expand_and_delete_garbage(T_STRING *line)
{
	T_STRING	tmp;

	tmp = *line;
	*line = expand(*line);
	free(tmp);
}

T_STRING	expand(T_STRING s)
{
	int			i;
	T_STRING	buff;
	T_STRING	expanded_str;
	int			len;
	int			res;

	len = str_len(s);
	i = -1;
	expanded_str = "";
	while (++i < len)
	{
		buff = "";
		if (s[i] == '$' && ++i)
		{
			res = get_var_value(s, &expanded_str, &i, &buff);
			i--;
			if (res == 1)
				break ;
			else if (res == 2)
				continue ;
		}
		else
			expanded_str = join_c(expanded_str, s[i]);
	}
	return (expanded_str);
}
