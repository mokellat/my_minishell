/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_fun_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 15:20:37 by mokellat          #+#    #+#             */
/*   Updated: 2021/09/27 04:29:21 by hamza            ###   ########.fr       */
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

int		is_quote(int c)
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
	if (is_single)
		return expand(new_str);
	return (new_str);
}

void	args_and_expand(t_pars_vars *vars, char **str)
{
	int			i;
	int			start;
	int			end;
	T_STRING	arg;

	arg = "";
	vars->is_quoted = 0;
	start = vars->k;
	end = vars->k;
	while (vars->x < vars->dif)
	{
		if((i = is_quote(str[vars->i][vars->k])) &&((is_quote(str[vars->i][vars->k]) == vars->is_quoted) || vars->is_quoted == 0))
		{
			if (is_quote(str[vars->i][vars->k]) == vars->is_quoted)
			{
				end = vars->k;
				arg = join(arg, custom_substr(str[vars->i], start + 1, end, vars->is_quoted));
				vars->is_quoted = 0;
				end++;
			}
			else
			{
				if (vars->is_quoted == 0 && end != (vars->k - 1))
					arg = join(arg, custom_substr(str[vars->i], end, vars->k, FALSE));
				start = vars->k;
				vars->is_quoted = i;
			}
		}
		vars->k++;
		vars->x++;
	}
	if (end != (vars->k - 1))
		arg = join(arg, custom_substr(str[vars->i], end, vars->k, FALSE));
	vars->final_str[vars->i].args[vars->y] = arg;
	vars->k = vars->j + 1;
	vars->x = 0;
	(vars->y)++;
}
