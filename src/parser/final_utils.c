/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 18:05:09 by hmellahi          #+#    #+#             */
/*   Updated: 2021/09/27 22:19:50 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(int c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}

T_STRING	custom_substr(T_STRING str, int start, int end, int is_single)
{
	T_STRING	new_str;

	new_str = sub_str(str, start, end - start);
	if (is_single != 1)
		return (expand(new_str));
	return (new_str);
}

void	args_expand_exec(t_pars_vars *vars,
char **str, int *start, int *end)
{
	int	i;

	i = is_quote(str[vars->i][vars->k]);
	if (i && ((is_quote(str[vars->i]
					[vars->k]) == vars->is_quoted) || vars->is_quoted == 0))
	{
		if (is_quote(str[vars->i][vars->k]) == vars->is_quoted)
		{
			*end = vars->k;
			vars->arg = join(vars->arg, custom_substr(str[vars->i], *start + 1,
						*end, vars->is_quoted));
			vars->is_quoted = 0;
			(*end)++;
		}
		else
		{
			if (vars->is_quoted == 0 && *end != vars->k)
				vars->arg = join(vars->arg, custom_substr(str[vars->i],
							*end, vars->k, FALSE));
			*start = vars->k;
			vars->is_quoted = i;
		}
	}
	vars->k++;
	vars->x++;
}
