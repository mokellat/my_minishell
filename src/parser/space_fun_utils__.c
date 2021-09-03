/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_fun_utils__.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:05:56 by mokellat          #+#    #+#             */
/*   Updated: 2021/09/03 18:40:42 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	before_delimiter(t_pars_vars *vars ,char **str)
{
	if (vars->j > 0 && (str[vars->i][vars->j - 1] == '>' || str[vars->i][vars->j - 1] == '<'))
	{
		vars->j--;
		redirections(vars, str);
		quoted(vars, str);
		vars->final_str[vars->i].files[vars->files_i].name
			= malloc(vars->redi_lenght - vars->j + 2);
		vars->redi_lenght = 0;
		is_quoted_assign(vars, str);
		if (!ft_strcmp(vars->final_str[vars->i].files[vars->files_i].name, "\0"))
		{
			write(2, "syntax error\n", 14);
			exit(EXIT_FAILURE);
		}
		vars->final_str[vars->i].files[vars->files_i].name[vars->redi_lenght] = 0;
		vars->final_str[vars->i].files[vars->files_i].name
			= ft_strtrim(vars->final_str[vars->i].files[vars->files_i].name, "\'\"");
		vars->files_i++;
		vars->final_str[vars->i].files_count++;
	}
	skip_quotes(vars, str);
}

void	after_delimiter(t_pars_vars *vars ,char **str)
{
	if (vars->y > 0)
	{
		vars->final_str[vars->i].n++;
		vars->final_str[vars->i].args = realloc(vars->final_str[vars->i].args,
				sizeof(char *) * (vars->final_str[vars->i].n));
	}
	vars->final_str[vars->i].args[vars->y] = (char *)malloc(vars->dif + 1);
	args_and_expand(vars, str);
}

void	check_redi_null(t_pars_vars *vars ,char **str)
{
	if (vars->j > 0 && (str[vars->i][vars->j - 1] == '>' || str[vars->i][vars->j - 1] == '<'))
	{
		write(2, "syntax error\n", 14);
		exit(EXIT_FAILURE);
	}
}