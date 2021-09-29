/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:14:01 by hmellahi          #+#    #+#             */
/*   Updated: 2021/09/27 18:43:37 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_H
# define CMDS_H

# include "macros.h"

typedef struct s_res
{
	T_STRING	output;
	int			status;
}				t_res;

typedef struct s_env
{
	t_vector	keys;
	t_vector	values;
}				t_env;

typedef struct s_error
{
	T_STRING	msg;
	int			status_code;
}				t_error;

typedef struct s_shell
{
	T_STRING	name;
	T_STRING	curr_dir;
	T_STRING	*cmds_str;
	t_env		env;
	int			depth;
	int			exit_code;
	t_bool		print_nl;
	T_STRING	term;
	t_res		(*(*cmds)(int i))(struct s_shell * this,
		T_STRING * args, int n);
	int			status_code;
	int			n_flag;
	T_STRING	cmd;
	char		ctrl_c_catched;
	int			stdin_fd_cpy;
	char		in_heredoc;
	char		redir_has_error;
	int			in;
	int			out;
	int			last;
	int			n;
	int			**fd;
	int			is_builtin;
	int			counter;
	int			in_child;
	int			is_exit_printed;
}				t_shell;

T_STRING	*init_cmds_str(void);
t_res (*cmds(int i))(t_shell * shell, char **args, int n);
t_res		cmd_exit(t_shell *shell, T_STRING *args, int n);
t_res		cmd_pwd(t_shell *shell, T_STRING *args, int n);
t_res		cmd_cd(t_shell *shell, T_STRING *args, int n);
t_res		cmd_export(t_shell *shell, T_STRING *args, int n);
t_res		cmd_echo(t_shell *shell, T_STRING *args, int n);
t_res		cmd_unset(t_shell *shell, T_STRING *args, int n);
t_res		cmd_env(t_shell *shell, T_STRING *args, int n);
#endif
