/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 09:52:17 by hmellahi          #+#    #+#             */
/*   Updated: 2021/09/29 14:30:22 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_signals(void)
{
	signal(CTRL_C, handle_signal);
	signal(CTRL_S, handle_signal);
}

int	handle_ctrl_c(T_STRING *line, t_shell *shell)
{
	(void)line;
	free(*line);
	shell->ctrl_c_catched = false;
	dup2(shell->stdin_fd_cpy, 0);
	close(shell->stdin_fd_cpy);
	return (1);
}

void	catch_ctrl_c(t_shell *shell)
{
	shell->exit_code = 1;
	if (!shell->in_heredoc)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		shell->ctrl_c_catched = true;
		shell->stdin_fd_cpy = dup(0);
		close(0);
	}
	shell_ref(shell);
}

void	handle_signal(int event_code)
{	
	t_shell		*shell;

	(void)event_code;
	shell = shell_ref(NULL);
	if (shell->in_child)
		return ;
	if (event_code == CTRL_C)
		catch_ctrl_c(shell);
	else if (event_code == CTRL_S)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	close_all_pipes(int **fd, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
}
