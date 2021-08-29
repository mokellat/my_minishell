/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 16:37:47 by hmellahi          #+#    #+#             */
/*   Updated: 2021/07/10 14:17:51 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_string	*init_cmds_str(void)
{
	t_string	*cmds_str;

	cmds_str = sf_malloc(sizeof(t_string) * (CMDS_COUNT + 1), ADD);
	cmds_str[0] = "exit";
	cmds_str[1] = "pwd";
	cmds_str[2] = "cd";
	cmds_str[3] = "export";
	cmds_str[4] = "echo";
	cmds_str[5] = "env";
	cmds_str[6] = "unset";
	cmds_str[7] = 0;
	return (cmds_str);
}

t_res (*cmds(int i))(t_shell * shell, char **args){
t_res (*funcs[8])(t_shell * shell, char **args);
funcs[0] = &cmd_exit;
funcs[1] = &cmd_pwd;
funcs[2] = &cmd_cd;
funcs[3] = &cmd_export;
funcs[4] = &cmd_echo;
funcs[5] = &cmd_env;
funcs[6] = &cmd_unset;
funcs[7] = NULL;return (funcs[i]);
}
