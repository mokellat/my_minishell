/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_fun_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 15:20:37 by mokellat          #+#    #+#             */
/*   Updated: 2021/09/29 11:45:55 by hmellahi         ###   ########.fr       */
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
	if (str[vars->i][vars->j] && (str[vars->i][vars->j] == '\''
		|| str[vars->i][vars->j] == '\"'))
	{
		if (str[vars->i][vars->j] == '\'')
			vars->final_str[vars->i].files[vars->files_i].is_quoted
				= SINGLE_QUOTE;
		else if (str[vars->i][vars->j] == '\"')
			vars->final_str[vars->i].files[vars->files_i].is_quoted
				= DOUBLE_QUOTE;
		vars->j++;
		vars->redi_lenght = vars->j;
		while (str[vars->i][vars->redi_lenght] && str[vars->i]
			[vars->redi_lenght] != '\'')
			vars->redi_lenght++;
		check_name_after(str, vars);
	}
	else
	{
		vars->redi_lenght = vars->j;
		vars->final_str[vars->i].files[vars->files_i].is_quoted = 0;
		while (str[vars->i][vars->redi_lenght] && str[vars->i]
			[vars->redi_lenght] != ' ')
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
				vars->final_str[vars->i].files[vars->files_i]
					.name[vars->redi_lenght++] = str[vars->i][vars->j++];
		}
		else if (vars->final_str[vars->i].files[vars->files_i].is_quoted
			== DOUBLE_QUOTE)
		{
			while (str[vars->i][vars->j] && str[vars->i][vars->j] != '\"')
				vars->final_str[vars->i].files[vars->files_i]
					.name[vars->redi_lenght++] = str[vars->i][vars->j++];
		}
		assign_name_after(str, vars);
	}
	else
	{
		while (str[vars->i][vars->j] && str[vars->i][vars->j] != ' ')
			vars->final_str[vars->i].files[vars->files_i]
				.name[vars->redi_lenght++] = str[vars->i][vars->j++];
	}
}

void	skip_quotes(t_pars_vars *vars, char **str)
{
	if (str[vars->i][vars->j] && str[vars->i][vars->j] == '\'')
	{
		vars->j++;
		while (str[vars->i][vars->j] && str[vars->i][vars->j] != '\'')
			vars->j++;
		vars->name_is_quoted = 1;
	}
	else if (str[vars->i][vars->j] && str[vars->i][vars->j] == '\"')
	{
		vars->j++;
		while (str[vars->i][vars->j] && str[vars->i][vars->j] != '\"')
			vars->j++;
		vars->name_is_quoted = 2;
	}
}

void	args_and_expand(t_pars_vars *vars, char **str)
{
	int			start;
	int			end;

	vars->arg = "";
	vars->is_quoted = 0;
	start = vars->k;
	end = vars->k;
	while (vars->x < vars->dif)
		args_expand_exec(vars, str, &start, &end);
	if (end != vars->k)
		vars->arg = join(vars->arg,
				custom_substr(str[vars->i], end, vars->k, FALSE));
	if (vars->is_quoted != 0 && !str_len(vars->arg))
		vars->final_str[vars->i].is_empty_string_quoted = 1;
	vars->final_str[vars->i].args[vars->y] = vars->arg;
	vars->k = vars->j + 1;
	vars->x = 0;
	(vars->y)++;
}
