/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:15:48 by hmellahi          #+#    #+#             */
/*   Updated: 2021/07/15 19:28:33 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcpy(char *dst, const char *src)
{
	int		i;

	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}

t_res	cmd_pwd(t_shell *shell, t_string *args)
{
	t_res	res;
	char	cwd[1024];

	(void)args;
	getcwd(cwd, sizeof(cwd));
	shell->curr_dir = str_dup(cwd);
	res.status = TRUE;
	res.output = shell->curr_dir;
	shell->exit_code = 0;
	res.output = join(cwd, "\n");
	return (res);
}
