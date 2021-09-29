/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_fun_utils__.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:05:56 by mokellat          #+#    #+#             */
/*   Updated: 2021/09/28 01:23:36 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	before_delimiter(t_pars_vars *vars, char **str)
{
	if (vars->j > 0 && (str[vars->i][vars->j - 1] == '>'
		|| str[vars->i][vars->j - 1] == '<'))
	{
		vars->j--;
		redirections(vars, str);
		quoted(vars, str);
		vars->final_str[vars->i].files[vars->files_i].name
			= sf_malloc(vars->redi_lenght - vars->j + 2, ADD);
		vars->redi_lenght = 0;
		is_quoted_assign(vars, str);
		if (!ft_strcmp(vars->final_str[vars->i].files[vars->files_i].name, "\0"))
			return (0);
		vars->final_str[vars->i].files[vars->files_i].name[vars->redi_lenght]
			= 0;
		vars->final_str[vars->i].files[vars->files_i].name
			= ft_strtrim
			(vars->final_str[vars->i].files[vars->files_i].name, "\'\"");
		vars->files_i++;
		vars->final_str[vars->i].files_count++;
	}
	skip_quotes(vars, str);
	return (1);
}

void	after_delimiter(t_pars_vars *vars, char **str)
{
	if (vars->y > 0)
	{
		vars->final_str[vars->i].args
			= ft_reallocate(vars->final_str[vars->i].args,
				vars->final_str[vars->i].n);
		vars->final_str[vars->i].n++;
	}
	vars->final_str[vars->i].args[vars->y]
		= (char *)sf_malloc(vars->dif + 1, ADD);
	args_and_expand(vars, str);
}

int	check_redi_null(t_pars_vars *vars, char **str)
{
	if (vars->j > 0 && (str[vars->i][vars->j - 1] == '>'
		|| str[vars->i][vars->j - 1] == '<'))
		return (0);
	return (1);
}

void	check_name_after(char **str, t_pars_vars *vars)
{
	if (str[vars->i][vars->redi_lenght] && (str[vars->i][vars->redi_lenght
		+ 1] != '\0' || str[vars->i][vars->redi_lenght + 1] != ' '))
	{
		vars->redi_lenght++;
		if (str[vars->i][vars->redi_lenght] == '\'')
		{
			vars->redi_lenght++;
			while (str[vars->i][vars->redi_lenght] && str[vars->i]
				[vars->redi_lenght] != '\'')
				vars->redi_lenght++;
		}
		else if (str[vars->i][vars->redi_lenght] == '\"')
		{
			vars->redi_lenght++;
			while (str[vars->i][vars->redi_lenght] &&
				str[vars->i][vars->redi_lenght] != '\"')
				vars->redi_lenght++;
		}
		else
		{
			while (str[vars->i][vars->redi_lenght] &&
				str[vars->i][vars->redi_lenght] != ' ')
				vars->redi_lenght++;
		}
	}
}

void	assign_name_after(char **str, t_pars_vars *vars)
{
	if (str[vars->i][vars->j] && (str[vars->i][vars->j + 1] != '\0'
		|| str[vars->i][vars->j + 1] != ' '))
	{
		vars->j++;
		if (str[vars->i][vars->j] == '\'')
		{
			vars->j++;
			while (str[vars->i][vars->j] && str[vars->i][vars->j] != '\'')
				vars->final_str[vars->i].files[vars->files_i]
					.name[vars->redi_lenght++] = str[vars->i][vars->j++];
		}
		else if (str[vars->i][vars->j] == '\"')
		{
			vars->j++;
			while (str[vars->i][vars->j] && str[vars->i][vars->j] != '\"')
				vars->final_str[vars->i].files[vars->files_i]
					.name[vars->redi_lenght++] = str[vars->i][vars->j++];
		}
		else
		{
			while (str[vars->i][vars->j] && str[vars->i][vars->j] != ' ')
				vars->final_str[vars->i].files[vars->files_i]
					.name[vars->redi_lenght++] = str[vars->i][vars->j++];
		}
	}
}
