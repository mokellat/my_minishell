/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:14:31 by hmellahi          #+#    #+#             */
/*   Updated: 2021/08/12 21:02:42 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_cur_dir(t_shell *shell)
{
	int		index;

	shell->exit_code = 0;
	index = vector_find(&shell->env.keys, "OLDPWD");
	if (index != -1)
		vector_set(&shell->env.values, index, shell->curr_dir);
	else
	{
		vector_push_back(&shell->env.keys, "OLDPWD");
		vector_push_back(&shell->env.values, shell->curr_dir);
	}
	cmd_pwd(shell, NULL);
	index = vector_find(&shell->env.keys, "PWD");
	printf("%d\n", index);
	vector_set(&shell->env.values, index, shell->curr_dir);
}

int	mv_to_old_pwd(t_shell *shell, t_string *path)
{
	if (vector_find(&shell->env.keys, "OLDPWD") == -1)
	{
		print_err("cd", OLDPWD_NOT_SET);
		return (FALSE);
	}
	*path = get_env(shell, "OLDPWD");
	return (TRUE);
}

t_res	cmd_cd(t_shell *shell, t_string *args)
{
	t_res		res;
	t_string	path;
	int			cd_ret;

	res.status = TRUE;
	res.output = "";
	path = args[1];
	shell->exit_code = 1;
	if (tablen(args) > 2)
	{
		print_err("cd", TOO_MANY_ARGS);
		return (res);
	}
	if (path == NULL)
		path = get_env(shell, "HOME");
	else if (str_cmp(path, "-") && !mv_to_old_pwd(shell, &path))
		return (res);
	cd_ret = chdir(path);
	if (cd_ret != 0) // not working oldpwd not setted
		print_err("cd", FILE_OR_DIR_NOT_FOUND);
	else
		change_cur_dir(shell);
	return (res);
}
