/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 12:16:50 by hmellahi          #+#    #+#             */
/*   Updated: 2021/09/20 18:53:47 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_signals(void)
{
	signal(CTRL_C, handle_signal);
	signal(CTRL_S, handle_signal);
}

int	handle_ctrl_c(t_shell *shell)
{
	put_str("\n");
	rl_replace_line("", 0);
	rl_redisplay();
	return (1);
}

void	handle_signal(int event_code)
{
	t_shell		*shell;

	(void)event_code;
	shell = shell_ref(NULL);
	if (event_code == CTRL_C)
	{
		if (shell->in_heredoc || shell->counter)
			printf("\n");
		shell->exit_code = 1;
		shell->ctrl_c_catched = true;
		shell->stdin_fd_cpy = dup(0);
		close(0);
		shell_ref(shell);
	}
	else if (event_code == CTRL_S)
	{
		if (!shell->in_child)
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
}
