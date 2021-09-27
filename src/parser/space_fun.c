/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_fun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:08:44 by mokellat          #+#    #+#             */
/*   Updated: 2021/07/29 16:14:19 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	inside_single_quotes(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\'')
		return (1);
	return (0);
}

void	init_program(t_pars_vars *pars_vars, char **str)
{
	pars_vars->j = 0;
	pars_vars->k = 0;
	pars_vars->y = 0;
	pars_vars->files_i = 0;
	pars_vars->final_str[pars_vars->i].n = 1;
	pars_vars->final_str[pars_vars->i].args
		= sf_malloc(
			sizeof(char *) * (pars_vars->final_str[pars_vars->i].n), ADD);
	pars_vars->final_str[pars_vars->i].args[0] = NULL;
	pars_vars->final_str[pars_vars->i].files
		= sf_malloc(sizeof(t_file) * 100, ADD);
	pars_vars->final_str[pars_vars->i].files_count = 0;
	str[pars_vars->i] = ft_strtrim(str[pars_vars->i], " ");
	pars_vars->check = 0;
	pars_vars->name_is_quoted = 0;
	pars_vars->final_str[pars_vars->i].is_empty_string_quoted = 0;
}

void	init_program__(t_pars_vars *vars, int num_strct)
{
	vars->i = 0;
	vars->x = 0;
	vars->final_str = sf_malloc(sizeof(t_cmd) * num_strct, ADD);
}

void	skip_redi_spaces(t_pars_vars *vars, char **str)
{
	if (vars->k > 0 && (str[vars->i][vars->k - 1] == '>'
		|| str[vars->i][vars->k - 1] == '<'))
	{
		vars->j++;
		vars->k = vars->j;
		vars->check = 1;
	}
	if (!vars->check && str[vars->i][vars->k] == ' ')
	{
		vars->check = 1;
		while (str[vars->i][vars->k] && str[vars->i][vars->k] == ' ')
			vars->k++;
		vars->j = vars->k;
	}
	vars->dif = vars->j - vars->k;
	if (!vars->check && (str[vars->i][vars->k] == '>'
		|| str[vars->i][vars->k] == '<'))
	{
		vars->check = 1;
		vars->j++;
		vars->k++;
	}
	if (!vars->check && str[vars->i][vars->j + 1] == '\0')
		vars->dif = vars->j - vars->k + 1;
}

// T_STRING	expands(T_STRING	line, t_pars_vars *vars)
// {
// 	int		i;

// 	i = -1;
// 	while (line[++vars->i])
// 	{
// 		if ()

// 	}
// 	return (line);	
// }

t_cmd	*space_delimiter_func(char **str, char *delimiter, int num_strct)
{
	t_pars_vars	vars;

	init_program__(&vars, num_strct);
	while (str[vars.i])
	{
		init_program(&vars, str);
		while (vars.j < (int)str_len(str[vars.i]))
		{
			vars.check = 0;
			if (!before_delimiter(&vars, str))
				return (NULL);
			if (str[vars.i][vars.j] && (ft_strrchr(delimiter,
				str[vars.i][vars.j]) || str[vars.i][vars.j + 1] == '\0'))
				set_vars_check(&vars, str);
			if (!vars.check)
				vars.j++;
		}
		if (!check_redi_null(&vars, str))
			return (NULL);
		vars.i++;
	}
	return (vars.final_str);
}
