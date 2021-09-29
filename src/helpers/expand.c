/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:59:06 by hmellahi          #+#    #+#             */
/*   Updated: 2021/09/29 15:01:25 by hmellahi         ###   ########.fr       */
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
	if (val)
		*expanded_str = join(*expanded_str, val);
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
	expanded_str = str_dup("");
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

int	run_heredoc(T_STRING *line, T_STRING *buff,
T_STRING source, char is_quoted)
{
	while (1)
	{
		++shell_ref(NULL)->in_heredoc;
		*line = readline("> ");
		shell_ref(NULL)->in_heredoc--;
		if (shell_ref(NULL)->ctrl_c_catched == true)
		{
			free(*line);
			return (handle_ctrl_c(line, shell_ref(NULL)) * 0 - 1);
		}
		if (!(*line) || str_cmp(*line, source))
			break ;
		if (!is_quoted)
			expand_and_delete_garbage(&*line);
		*buff = join(*buff, *line);
		*buff = join(*buff, "\n");
		if (*line)
			free(*line);
	}
	return (0);
}
