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
		= malloc(sizeof(char *) * (pars_vars->final_str[pars_vars->i].n));
	pars_vars->final_str[pars_vars->i].files
		= malloc(sizeof(t_file) * 100);
	pars_vars->final_str[pars_vars->i].files_count = 0;
	str[pars_vars->i] = ft_strtrim(str[pars_vars->i], " ");
}

t_cmd	*space_delimiter_func(char **str, char *delimiter, int num_strct)
{
	t_pars_vars	pars_vars;

	pars_vars.i = 0;
	pars_vars.x = 0; 
	pars_vars.final_str = malloc(sizeof(t_cmd) * num_strct);
	while (str[pars_vars.i])
	{
		init_program(&pars_vars, str);
		while (pars_vars.j < (int)str_len(str[pars_vars.i]))
		{
			before_delimiter(&pars_vars, str);
			if (str[pars_vars.i][pars_vars.j] && (ft_strrchr(delimiter, str[pars_vars.i][pars_vars.j])
				|| str[pars_vars.i][pars_vars.j + 1] == '\0'))
			{
				if (pars_vars.k > 0 && (str[pars_vars.i][pars_vars.k - 1] == '>' || str[pars_vars.i][pars_vars.k - 1] == '<'))
				{
					pars_vars.j++;
					pars_vars.k = pars_vars.j;
					continue ;
				}
				if (str[pars_vars.i][pars_vars.k] == ' ')
				{
					while (str[pars_vars.i][pars_vars.k] && str[pars_vars.i][pars_vars.k] == ' ')
						pars_vars.k++;
					pars_vars.j = pars_vars.k;
					continue ;
				}
				pars_vars.dif = pars_vars.j - pars_vars.k;
				if ((str[pars_vars.i][pars_vars.k] == '>' || str[pars_vars.i][pars_vars.k] == '<'))
				{
					pars_vars.j++;
					pars_vars.k++;
					continue ;
				}
				if (str[pars_vars.i][pars_vars.j + 1] == '\0')
					pars_vars.dif = pars_vars.j - pars_vars.k + 1;
				after_delimiter(&pars_vars, str);
			}
			pars_vars.j++;
		}
		check_redi_null(&pars_vars, str);
		pars_vars.i++;
	}
	return (pars_vars.final_str);
}
