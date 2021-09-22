/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:42:09 by hmellahi          #+#    #+#             */
/*   Updated: 2021/09/22 17:44:06 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory(T_STRING path)
{
	DIR		*dir;
	int		flag;

	flag = 0;
	dir = opendir(path);
	if (dir != NULL)
	{
		flag = 1;
		closedir(dir);
	}
	return (flag);
}

int	parse(T_STRING line, t_cmd **cmds)
{
	t_split_pipe	pipe_split;
	t_cmd			*final_str;
	int				j;
	int				i;

	if (!open_quotes(line))
		return ((print_err("", SYNTAX_ERROR) * 0) - 1);
	pipe_split.pipe_str = split_delimiter_func(line,
			'|', pipe_split.pipe_str, &pipe_split.num_tab);
	final_str = space_delimiter_func(pipe_split.pipe_str,
			" <>", pipe_split.num_tab);
	i = -1;
	while (++i < pipe_split.num_tab)
	{
		if (!multiple_red(pipe_split.pipe_str[i]))
			return ((print_err("", SYNTAX_ERROR) * 0) - 1);
		j = -1;
		while (++j < final_str[i].files_count)
			if (final_str[i].files[j].type == RED_IN_SOURCE)
				if (red_in_source(&(final_str[i].files[j])) == -1)
					return (-1);
		// j = -1;
		// while (++j < final_str[i].n)
		// {
		final_str[i].args = ft_reallocate(final_str[i].args, final_str[i].n);
		// for ( j = 0 ; j < final_str[i].n; j++)
		// 	puts(final_str[i].args[j]);
			// while ()
		// }
	}
	*cmds = final_str;
	return (pipe_split.num_tab);
}
