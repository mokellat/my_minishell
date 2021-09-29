/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 09:53:58 by hmellahi          #+#    #+#             */
/*   Updated: 2021/09/29 15:29:04 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*shell_ref(t_shell *shell)
{
	static t_shell	*ref;

	if (shell)
		ref = shell;
	return (ref);
}

int	main(int ac, char **argv, char **env_vars)
{
	t_shell	shell;

	(void)ac;
	shell.n_flag = 0;
	shell_ref(&shell);
	init_shell(&shell, env_vars);
	shell_loop(&shell);
	if (!shell.is_exit_printed)
		put_str("exit");
	sf_malloc(0, FREE);
	system("leaks minishell");
	return (shell.exit_code);
}
