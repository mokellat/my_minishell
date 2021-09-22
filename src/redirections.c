/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 05:50:16 by hamza             #+#    #+#             */
/*   Updated: 2021/09/22 17:52:23 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	red_out_app(t_redir *redir, t_file file)
{
	redir->out_file = open(file.name, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (redir->out_file == -1)
		return (PERMSSION_DENIED);
	return (0);
}

int	red_out(t_redir *redir, t_file file)
{
	redir->out_file = open(file.name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (redir->out_file == -1)
		return (PERMSSION_DENIED);
	return (0);
}

int	red_in(t_redir *redir, t_file file)
{
	struct stat	stats;
	int			is_exist;

	if (file.type == RED_IN_SOURCE)
	{
		redir->in_file = file.fd;
		return (0);
	}
	is_exist = stat(file.name, &stats);
	if (is_exist == -1)
		return (NOT_FOUND);
	redir->in_file = open(file.name, O_RDONLY);
	if (redir->in_file == -1)
		return (PERMSSION_DENIED);
	return (0);
}

// #define HERE fprintf(stderr, "here: %s:%d\n", __FILE__, __LINE__)
int	red_in_source(t_file *f)
{
	T_STRING	source;
	T_STRING	line;
	T_STRING	buff;
	int			fd[2];

	(pipe(fd) || 1) && (source = f->name);
	f->fd = fd[0];
	buff = "";
	while (1)
	{
		++shell_ref(NULL)->in_heredoc && (line = readline("> "));
		shell_ref(NULL)->in_heredoc--;
		if (shell_ref(NULL)->ctrl_c_catched == true)
		{
			free(line);
			return (handle_ctrl_c(shell_ref(NULL)) * 0 - 1);
		}
		else if (!line || str_cmp(line, source))
			break ;
		if (f->is_quoted != SINGLE_QUOTE)
			line = expand(line);
		buff = join(buff, line);
		buff = join(buff, "\n");
		free(line);
	}
	buff && fput_str(buff, fd[1]);
	free(line);
	return (0 * close(fd[1]));
}

t_redir	check_for_redirections(t_cmd *cmd)
{
	int			i;
	t_file		*files;
	t_redir		redir;

	redir.out_file = 0;
	redir.in_file = 0;
	redir.err = 0;
	files = cmd->files;
	i = -1;
	while (++i < cmd->files_count)
	{
		if ((files[i].type == RED_IN
				|| files[i].type == RED_IN_SOURCE))
			redir.err = red_in(&redir, files[i]);
		else if (files[i].type == RED_OUT)
			redir.err = red_out(&redir, files[i]);
		else if (files[i].type == RED_OUT_AP)
			redir.err = red_out_app(&redir, files[i]);
		if (redir.err)
		{
			print_err(files[i].name, redir.err);
			return (redir);
		}
	}
	return (redir);
}
