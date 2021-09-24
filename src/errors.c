/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 02:08:53 by hamza             #+#    #+#             */
/*   Updated: 2021/09/24 00:53:12 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	new_error(T_STRING msg, int status_code)
{
	t_error		err;

	err.msg = msg;
	err.status_code = status_code;
	return (err);
}

t_error	get_err_msg(int index)
{
	t_error	*errors;

	errors = sf_malloc(sizeof(t_error) * 11, ADD);
	errors[0] = new_error("too many arguments", 1);
	errors[1] = new_error("No such file or directory", 127);
	errors[2] = new_error("command not found", 127);
	errors[3] = new_error("permission denied", 126);
	errors[4] = new_error("is a directory", 126);
	errors[5] = new_error("numeric argument required", 255);
	errors[6] = new_error("not a valid identifier", 1);
	errors[7] = new_error("OLDPWD not set", 1);
	errors[10] = new_error("syntax error", 258);
	return (errors[index]);
}

int	print_err(T_STRING path, int error_index)
{
	T_STRING	error;
	t_error		error_msg;
	int			status_code;

	error = join("minishell: ", path);
	error_msg = get_err_msg(error_index);
	if (*path)
		error = join(error, " : ");
	error = join(error, error_msg.msg);
	error = join(error, "\n");
	fput_str(error, STDERR_FILENO);
	status_code = error_msg.status_code;
	return (status_code);
}
