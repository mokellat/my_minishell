/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 12:16:50 by hmellahi          #+#    #+#             */
/*   Updated: 2021/08/12 22:51:59 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_signals(void)
{
	signal(CTRL_C, handle_signal);
	signal(CTRL_S, handle_signal);
	// signal(SIGKILL, handle_signal);
	// signal(SIGBUS, handle_signal);
}

int	handle_ctrl_c(t_shell *shell)
{
	shell->ctrl_c_catched = false;
	dup2(shell->stdin_fd_cpy, 0);
	close(shell->stdin_fd_cpy);
	// shell->counter = FALSE;
	return (1);
}

void	handle_signal(int event_code)
{
	t_shell		*shell;

	(void)event_code;
	if (event_code == CTRL_C)
	{
		shell = shell_ref(NULL);
		if (shell->in_heredoc || shell->counter)
			printf("\n");
		shell->exit_code = 1;
		shell->ctrl_c_catched = true;
		shell->stdin_fd_cpy = dup(0);
		close(0);
		shell_ref(shell);
	}
}
