/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:42:09 by hmellahi          #+#    #+#             */
/*   Updated: 2021/08/12 22:41:55 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory(t_string path)
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

int	parse(t_string line, t_cmd **cmds)
{
	t_split_pipe	pipe_split;
	t_cmd			*final_str;
	int				j;

	if(!open_quotes(line))
		return ((print_err("", SYNTAX_ERROR) * 0) - 1);
	pipe_split.pipe_str = split_delimiter_func(line,
							'|', pipe_split.pipe_str, &pipe_split.num_tab);
	final_str = space_delimiter_func(pipe_split.pipe_str, " <>", pipe_split.num_tab);
	for(int i = 0; i < pipe_split.num_tab; i++)
	{
		if(!multiple_red(pipe_split.pipe_str[i]))
			return ((print_err("", SYNTAX_ERROR) * 0) - 1);
		j = -1;
		while (++j < final_str[i].files_count)
			if (final_str[i].files[j].type == RED_IN_SOURCE)
				if (red_in_source(&(final_str[i].files[j])) == -1)
					return (-1);
	}
	*cmds = final_str;
	return (pipe_split.num_tab);
}
