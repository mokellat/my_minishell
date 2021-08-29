/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:14:43 by hmellahi          #+#    #+#             */
/*   Updated: 2021/08/12 22:51:28 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_string	*env_to_arr(t_env *env)
{
	t_string	*env_arr;
	int			i;
	t_string	key;
	t_string	value;

	i = -1;
	env_arr = sf_malloc(sizeof(t_string) * (env->keys.size + 1), ADD);
	while (++i < env->keys.size)
	{
		key = vector_get(&env->keys, i);
		value = vector_get(&env->values, i);
		env_arr[i] = join(key, "=");
		env_arr[i] = join(env_arr[i], value);
	}
	env_arr[i] = NULL;
	return (env_arr);
}

t_string	get_exec_path(t_shell *shell,
			t_string *args, struct stat stats, int *status)
{
	t_string	*paths;
	t_string	path_var;
	t_string	path;
	int			i;

	path_var = get_env(shell, "PATH");
	paths = split(path_var, ':');
	if (*status == -1 && strlen(args[0]) > 2
		&& args[0][0] == '.' && args[0][1] == '/')
		print_err(args[0], FILE_OR_DIR_NOT_FOUND);
	i = -1;
	while (paths[++i] && *status == -1)
	{
		path = join(paths[i], "/");
		*status = stat(join(path, args[0]), &stats);
	}
	return (path);
}

int	shell_launch(t_shell *shell, t_string *args)
{
	int			status;
	struct stat	stats;
	int			exit_code;
	t_string	path;

	status = stat(args[0], &stats);
	path = get_exec_path(shell, args, stats, &status);
	if (status == -1)
		return (print_err(args[0], CMD_NOT_FOUND));
	status = execve(join(path, args[0]), args, env_to_arr(&shell->env));
	if (status == -1)
	{
		if (is_directory(args[0]))
			exit_code = print_err(args[0], IS_A_DIR);
		else
			exit_code = print_err(args[0], PERMSSION_DENIED);
	}
	else
		exit_code = 0;
	return (exit_code);
}

t_res	execute_builtin_cmd(t_string *args, t_shell *shell, int *is_builtin)
{
	int		i;
	t_res	res;

	i = -1;
	while (++i < CMDS_COUNT)
	{
		if (str_cmp(args[0], shell->cmds_str[i]) == TRUE)
		{
			res = ((*shell->cmds)(i))(shell, args);
			*is_builtin = TRUE;
			return (res);
		}
	}
	res.output = "";
	res.status = 0;
	return (res);
}

void	shell_loop(t_shell *shell)
{
	t_string	line;
	t_cmd		*cmds;
	t_res		result;
	int			ret;

	result.status = TRUE;
	shell->counter = TRUE;
	while (result.status)
	{
		line = readline("minishell$ ");
		if (shell->ctrl_c_catched == true && handle_ctrl_c(shell))
			continue ;
		else if (line && !*line)
			continue ;
		else if (!line)
			break ;
		add_history(line);
		ret = parse(line, &cmds);
		free(line);
		if (ret == -1 && (shell->exit_code = 2))
			continue ;
		result = fork_pipes(ret, cmds, shell);
		shell->counter = TRUE;
	}
}
