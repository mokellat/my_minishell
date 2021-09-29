/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:14:43 by hmellahi          #+#    #+#             */
/*   Updated: 2021/09/29 15:57:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

T_STRING	*env_to_arr(t_env *env, int flag)
{
	T_STRING	*env_arr;
	int			i;
	T_STRING	value;

	i = -1;
	env_arr = sf_malloc(sizeof(T_STRING) * (env->keys.size + 1), ADD);
	while (++i < env->keys.size)
	{
		env_arr[i] = vector_get(&env->keys, i);
		value = vector_get(&env->values, i);
		if (value)
		{
			env_arr[i] = join(env_arr[i], "=");
			if (flag)
				env_arr[i] = join(env_arr[i], "\"");
			env_arr[i] = join(env_arr[i], value);
			if (flag)
				env_arr[i] = join(env_arr[i], "\"");
		}
	}
	env_arr[i] = NULL;
	return (env_arr);
}

T_STRING	get_exec_path(t_shell *shell,
			T_STRING *args, struct stat stats, int *status)
{
	T_STRING	*paths;
	T_STRING	path_var;
	T_STRING	path;
	int			i;

	path_var = get_env(shell, "PATH");
	if (!path_var)
		return ("");
	paths = split(path_var, ':');
	if (*status == -1 && strlen(args[0]) > 2
		&& args[0][0] == '.' && args[0][1] == '/')
	{
		print_err(args[0], FILE_OR_DIR_NOT_FOUND);
		return (NULL);
	}
	i = -1;
	path = "";
	while (paths[++i] && *status == -1)
	{
		path = join(paths[i], "/");
		*status = stat(join(path, args[0]), &stats);
	}
	return (path);
}

int	shell_launch(t_shell *shell, T_STRING *args)
{
	int			status;
	struct stat	stats;
	int			exit_code;
	T_STRING	path;

	if (!args[0][0])
		return (print_err("''", CMD_NOT_FOUND));
	status = stat(args[0], &stats);
	path = get_exec_path(shell, args, stats, &status);
	if (!path)
		return (127);
	if (status == -1)
		return (print_err(args[0], CMD_NOT_FOUND));
	status = execve(join(path, args[0]), args, env_to_arr(&shell->env, FALSE));
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

t_res	execute_builtin_cmd(t_cmd cmd, t_shell *shell, int *is_builtin)
{
	int			i;
	t_res		res;
	T_STRING	*args;

	args = cmd.args;
	i = -1;
	while (++i < CMDS_COUNT)
	{
		if (str_cmp(args[0], shell->cmds_str[i]) == TRUE)
		{
			res = ((*shell->cmds)(i))(shell, args, cmd.n);
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
	T_STRING	line;
	t_cmd		*cmds;
	t_res		result;
	int			ret;

	result.status = TRUE;
	while (result.status)
	{
		line = readline("minishell$ ");
		if (line && !*line)
		{
			free(line);
			continue ;
		}
		else if (!line)
			break ;
		add_history(line);
		ret = parse(line, &cmds);
		free(line);
		if (ret == -1)
		{
			shell->exit_code = 258;
			continue ;
		}
		result = fork_pipes(ret, cmds, shell);
	}
}
