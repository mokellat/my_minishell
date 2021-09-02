/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_fun_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 15:20:37 by mokellat          #+#    #+#             */
/*   Updated: 2021/09/01 18:14:17 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirections(int i, int *j, char **str, t_cmd *final_str, int files_i)
{
	if (str[i][*j] == '>')
		final_str[i].files[files_i].type = RED_OUT;
	else if (str[i][*j] == '<')
		final_str[i].files[files_i].type = RED_IN;
	(*j)++;
	if (str[i][*j] == '>')
	{
		final_str[i].files[files_i].type = RED_OUT_AP;
		(*j)++;
	}
	else if (str[i][*j] == '<')
	{
		final_str[i].files[files_i].type = RED_IN_SOURCE;
		(*j)++;
	}
	while (str[i][*j] && str[i][*j] == ' ')
		(*j)++;
}

void	quoted(char **str, int i, int *j, t_cmd *final_str, int files_i, int *redi_lenght)
{
	if (str[i][*j] && (str[i][*j] == '\'' || str[i][*j] == '\"'))
	{
		if (str[i][*j] == '\'')
			final_str[i].files[files_i].is_quoted
				= SINGLE_QUOTE;
		else if (str[i][*j] == '\"')
			final_str[i].files[files_i].is_quoted
				= DOUBLE_QUOTE;
		(*j)++;
		*redi_lenght = *j;
		while (str[i][*redi_lenght] && str[i][*redi_lenght] != '\'')
			(*redi_lenght)++;
	}
	else
	{
		*redi_lenght = *j;
		final_str[i].files[files_i].is_quoted = 0;
		while (str[i][*redi_lenght] && str[i][*redi_lenght] != ' ')
			(*redi_lenght)++;
	}
}


void	is_quoted_assign(char **str, int i, int *j, t_cmd *final_str, int *redi_lenght, int files_i)
{
	if (final_str[i].files[files_i].is_quoted)
	{
		if (final_str[i].files[files_i].is_quoted
			== SINGLE_QUOTE)
		{
			while (str[i][*j] && str[i][*j] != '\'')
				final_str[i].files[files_i].name[(*redi_lenght)++]
					= str[i][(*j)++];
		}
		else if (final_str[i].files[files_i].is_quoted
			== DOUBLE_QUOTE)
		{
			while (str[i][*j] && str[i][*j] != '\"')
				final_str[i].files[files_i].name[(*redi_lenght)++]
					= str[i][(*j)++];
		}
		(*j)++;
	}
	else
	{
		while (str[i][*j] && str[i][*j] != ' ')
			final_str[i].files[files_i].name[(*redi_lenght)++]
				= str[i][(*j)++];
	}
}

void	skip_quotes(char **str, int i, int *j)
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

void	args_and_expand(char **str, int *x, int *dif, int *k, int i, int *y, int j,t_cmd *final_str)
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