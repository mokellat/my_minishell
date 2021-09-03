/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_fun_utils__.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:05:56 by mokellat          #+#    #+#             */
/*   Updated: 2021/09/03 15:38:13 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	before_delimiter(char **str, int *j, t_cmd *final_str, int i, int *files_i, int *redi_lenght)
{
	if (*j > 0 && (str[i][*j - 1] == '>' || str[i][*j - 1] == '<'))
	{
		(*j)--;
		redirections(i, j, str, final_str, *files_i);
		quoted(str, i, j, final_str, *files_i, redi_lenght);
		final_str[i].files[*files_i].name
			= malloc(*redi_lenght - *j + 2);
		*redi_lenght = 0;
		is_quoted_assign(str, i, j, final_str, redi_lenght, *files_i);
		if (!ft_strcmp(final_str[i].files[*files_i].name, "\0"))
		{
			write(2, "syntax error\n", 14);
			exit(EXIT_FAILURE);
		}
		final_str[i].files[*files_i].name[*redi_lenght] = 0;
		final_str[i].files[*files_i].name
			= ft_strtrim(final_str[i].files[*files_i].name, "\'\"");
		(*files_i)++;
		final_str[i].files_count++;
	}
	skip_quotes(str, i, j);
}

void	after_delimiter(char **str, int *x, int *dif, int *k, int i, int *y, int j,t_cmd *final_str)
{
	if (*y > 0)
	{
		final_str[i].n++;
		final_str[i].args = realloc(final_str[i].args,
				sizeof(char *) * (final_str[i].n));
	}
	final_str[i].args[*y] = (char *)malloc(*dif + 1);
	args_and_expand(str, x, dif, k, i, y, j, final_str);
}

void	check_redi_null(char **str, int i, int j)
{
	if (j > 0 && (str[i][j - 1] == '>' || str[i][j - 1] == '<'))
	{
		write(2, "syntax error\n", 14);
		exit(EXIT_FAILURE);
	}
}