/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_fun_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 15:20:37 by mokellat          #+#    #+#             */
/*   Updated: 2021/09/27 00:37:47 by marvin           ###   ########.fr       */
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

void	args_and_expand(t_pars_vars *vars, char **str)
{
	int	i;
	int	start;
	int	end;

	vars->is_quoted = 0;
	start = vars->k;
	end = vars->k;
	vars->final_str[vars->i].args[vars->y] = "";
	// printf("k : %d", vars->k);
	// while (vars->k < strlen(str[vars->i]))
	while (vars->x < vars->dif)
	{
		printf("%d|%d|%d\n", vars->k, vars->is_quoted, (is_quote(str[vars->i][vars->k]) == vars->is_quoted));
		if((i = is_quote(str[vars->i][vars->k])) && ((is_quote(str[vars->i][vars->k]) == vars->is_quoted) || vars->is_quoted == 0))
		{
			if (is_quote(str[vars->i][vars->k]) == vars->is_quoted)
			{
				// printf("s:%d, e:%d\n", start, end);
				end = vars->k;
				if (vars->is_quoted == 1)
				{
					printf("exp2 : %s\n", join( vars->final_str[vars->i].args[vars->y], sub_str(str[vars->i], start + 1, end - (start + 1))));
					vars->final_str[vars->i].args[vars->y] = join( vars->final_str[vars->i].args[vars->y], sub_str(str[vars->i], start + 1, end - (start + 1)));
				}
				else
				{
					printf("exp3 : %s\n",  join( vars->final_str[vars->i].args[vars->y], expand(sub_str(str[vars->i], start + 1, end - (start + 1)))));
					vars->final_str[vars->i].args[vars->y] = join( vars->final_str[vars->i].args[vars->y], expand(sub_str(str[vars->i], start + 1, end - (start + 1))));
				}
				vars->is_quoted = 0;
			}
			else
			{
				if (vars->is_quoted == 0 && end != (vars->k - 1))
				{
					// puts("hey");
					printf("exp : %s\n", join(vars->final_str[vars->i].args[vars->y], expand(sub_str(str[vars->i], end, vars->k  - end))));
					vars->final_str[vars->i].args[vars->y] = join(vars->final_str[vars->i].args[vars->y], expand(sub_str(str[vars->i], end, vars->k  - end - 1)));
				}
				start = vars->k;
				vars->is_quoted = i;
			}
			(vars->dif)--;
			// printf("at : %c\n", str[vars->i][vars->k]);
		}
			// vars->final_str[vars->i].args[vars->y][(vars->x)++]
			// 	= str[vars->i][(vars->k)++];
		vars->k++;
		vars->x++;
	}
	if (end != (vars->k - 1))
		vars->final_str[vars->i].args[vars->y] = join( vars->final_str[vars->i].args[vars->y], expand(sub_str(str[vars->i], end, vars->k  - end)));
	puts(vars->final_str[vars->i].args[vars->y]);
	// if (!inside_single_quotes(vars->final_str[vars->i].args[vars->y]))
	// {
	// 	if (vars->name_is_quoted == 0)
	// 		vars->final_str[vars->i].args[vars->y]
	// 			= expand(ft_strtrim(vars->final_str[vars->i].args[vars->y], "\'\""));
	// 	else if(vars->name_is_quoted == 1)
	// 		vars->final_str[vars->i].args[vars->y]
	// 			= expand(ft_strtrim(vars->final_str[vars->i].args[vars->y], "\'"));
	// 	else if (vars->name_is_quoted == 2)
	// 		vars->final_str[vars->i].args[vars->y]
	// 			= expand(ft_strtrim(vars->final_str[vars->i].args[vars->y], "\""));
	// }
	// else
	// {
	// 	if(vars->name_is_quoted == 1)
	// 		vars->final_str[vars->i].args[vars->y]
	// 			= ft_strtrim(vars->final_str[vars->i].args[vars->y], "\'");
	// 	else if(vars->name_is_quoted == 2)
	// 		vars->final_str[vars->i].args[vars->y]
	// 			= ft_strtrim(vars->final_str[vars->i].args[vars->y], "\"");
		
	// }
	vars->k = vars->j + 1;
	vars->x = 0;
	(vars->y)++;
}
