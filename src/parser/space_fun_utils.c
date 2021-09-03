/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_fun_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 15:20:37 by mokellat          #+#    #+#             */
/*   Updated: 2021/09/03 17:05:10 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirections(t_pars_vars *vars, char **str)
{
	if (str[vars->i][vars->j] == '>')
		vars->final_str[vars->i].files[vars->files_i].type = RED_OUT;
	else if (str[vars->i][vars->j] == '<')
		vars->final_str[vars->i].files[vars->files_i].type = RED_IN;
	vars->j++;
	if (str[vars->i][vars->j] == '>')
	{
		vars->final_str[vars->i].files[vars->files_i].type = RED_OUT_AP;
		vars->j++;
	}
	else if (str[vars->i][vars->j] == '<')
	{
		vars->final_str[vars->i].files[vars->files_i].type = RED_IN_SOURCE;
		vars->j++;
	}
	while (str[vars->i][vars->j] && str[vars->i][vars->j] == ' ')
		vars->j++;
}

void	quoted(t_pars_vars *vars, char **str)
{
	if (str[vars->i][vars->j] && (str[vars->i][vars->j] == '\'' || str[vars->i][vars->j] == '\"'))
	{
		if (str[vars->i][vars->j] == '\'')
			vars->final_str[vars->i].files[vars->files_i].is_quoted
				= SINGLE_QUOTE;
		else if (str[vars->i][vars->j] == '\"')
			vars->final_str[vars->i].files[vars->files_i].is_quoted
				= DOUBLE_QUOTE;
		vars->j++;
		vars->redi_lenght = vars->j;
		while (str[vars->i][vars->redi_lenght] && str[vars->i][vars->redi_lenght] != '\'')
			vars->redi_lenght++;
	}
	else
	{
		vars->redi_lenght = vars->j;
		vars->final_str[vars->i].files[vars->files_i].is_quoted = 0;
		while (str[vars->i][vars->redi_lenght] && str[vars->i][vars->redi_lenght] != ' ')
			vars->redi_lenght++;
	}
}


void	is_quoted_assign(t_pars_vars *vars, char **str)
{
	if (vars->final_str[vars->i].files[vars->files_i].is_quoted)
	{
		if (vars->final_str[vars->i].files[vars->files_i].is_quoted
			== SINGLE_QUOTE)
		{
			while (str[vars->i][vars->j] && str[vars->i][vars->j] != '\'')
				vars->final_str[vars->i].files[vars->files_i].name[vars->redi_lenght++]
					= str[vars->i][vars->j++];
		}
		else if (vars->final_str[vars->i].files[vars->files_i].is_quoted
			== DOUBLE_QUOTE)
		{
			while (str[vars->i][vars->j] && str[vars->i][vars->j] != '\"')
				vars->final_str[vars->i].files[vars->files_i].name[vars->redi_lenght++]
					= str[vars->i][vars->j++];
		}
		vars->j++;
	}
	else
	{
		while (str[vars->i][vars->j] && str[vars->i][vars->j] != ' ')
			vars->final_str[vars->i].files[vars->files_i].name[vars->redi_lenght++]
				= str[vars->i][vars->j++];
	}
}

void	skip_quotes(t_pars_vars *vars, char **str)
{
	if (str[i][*j] == '\'')
	{
		(*j)++;
		while (str[i][*j] && str[i][*j] != '\'')
			(*j)++;
	}
	else if (str[i][*j] == '\"')
	{
		(*j)++;
		while (str[i][*j] && str[i][*j] != '\"')
			(*j)++;
	}
}

void	args_and_expand(t_pars_vars *vars, char **str)
{
	while (*x < *dif)
	{
		if (k != 0 && str[i][*k] && str[i][*k] == '\'')
		{
			(*dif)--;
			(*k)++;
		}
		else
			final_str[i].args[*y][(*x)++] = str[i][(*k)++];
	}
	final_str[i].args[*y][*x] = '\0';
	if (!inside_single_quotes(final_str[i].args[*y]))
		final_str[i].args[*y]
			= expand(ft_strtrim(final_str[i].args[*y], "\'\""));
	else
		final_str[i].args[*y]
			= ft_strtrim(final_str[i].args[*y], "\'\"");
	*k = j + 1;
	*x = 0;
	(*y)++;
}