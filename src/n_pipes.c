/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_pipes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:50:04 by hmellahi          #+#    #+#             */
/*   Updated: 2021/09/29 11:54:39 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_shell *shell, t_redir redir, t_cmd cmd, t_res res)
{
	if (redir.in_file)
		shell->in = redir.in_file;
	if (shell->in != STDIN_FILENO)
	{
		dup2(shell->in, STDIN_FILENO);
		close(shell->in);
	}
	if (redir.out_file)
		shell->out = redir.out_file;
	if (shell->out != STDOUT_FILENO)
	{
		dup2(shell->out, STDOUT_FILENO);
		close(shell->out);
	}
	close(shell->fd[cmd.index][0]);
	close(shell->fd[cmd.index][1]);
	if (shell->n != 1)
		res = execute_builtin_cmd(cmd, shell, &shell->is_builtin);
	if (shell->is_builtin == TRUE && res.output)
		put_str(res.output);
	else
		shell->exit_code = shell_launch(shell, cmd.args);
	exit(shell->exit_code);
}

int	spawn_proc(t_cmd cmd, t_shell *shell)
{
	pid_t		pid;
	t_res		res;
	T_STRING	*args;
	t_redir		redir;

	redir = check_for_redirections(&cmd);
	shell->redir_has_error = false;
	args = cmd.args;
	if ((redir.out_file || redir.in_file) && !args[0])
		return (1);
	if (redir.err)
	{
		shell->exit_code = 1;
		shell->redir_has_error = true;
		return (shell->exit_code);
	}
	shell->is_builtin = 0;
	if (shell->n == 1)
		res = execute_builtin_cmd(cmd, shell, &shell->is_builtin);
	shell->last && (shell->out = 1);
	pid = fork();
	if (pid == 0)
		exec_cmd(shell, redir, cmd, res);
	return (!shell->is_builtin || (shell->is_builtin && res.status));
}

void	catch_child_proc_exit_status(t_shell *shell)
{
	int	wstatus;
	int	signal;

	while (wait(&wstatus) != -1)
		;
	if (WIFEXITED(wstatus))
		shell->exit_code = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
	{
		signal = WTERMSIG(wstatus);
		if (signal == SIGQUIT)
			put_str("Quit: 3\n");
		else if (signal == SIGINT)
			put_str("\n");
		shell->exit_code = signal + 128;
	}
}

void	spawn_procs(int n, t_cmd *cmd, t_shell *shell, t_res *res)
{
	int	i;

	i = -1;
	shell->in = 0;
	while (++i < n)
	{
		shell->fd[i][1] = -342332;
		shell->fd[i][0] = -342332;
		if (i == (n - 1))
			shell->last = TRUE;
		else
			pipe(shell->fd[i]);
		shell->out = shell->fd[i][1];
		cmd[i].index = i;
		res->status = spawn_proc(cmd[i], shell);
		close(shell->fd[i][1]);
		shell->in = shell->fd[i][0];
	}
}

t_res	fork_pipes(int n, t_cmd *cmd, t_shell *shell)
{
	int		i;
	t_res	res;

	res.status = TRUE;
	shell->in_child = 1;
	shell->fd = sf_malloc(sizeof(int *) * n, ADD);
	i = -1;
	while (++i < n)
		shell->fd[i] = sf_malloc(sizeof(int) * 2, ADD);
	shell->last = FALSE;
	shell->in = 0;
	shell->out = 1;
	shell->n = n;
	spawn_procs(n, cmd, shell, &res);
	close_all_pipes(shell->fd, n - 1);
	if (!shell->redir_has_error)
		catch_child_proc_exit_status(shell);
	shell->in_child = 0;
	return (res);
}
