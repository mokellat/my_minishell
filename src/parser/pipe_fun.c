/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:09:45 by mokellat          #+#    #+#             */
/*   Updated: 2021/07/13 20:05:31 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calcul_delimiter(char *str, char *delimiter)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i + 1] && str[i] != '\'')
				i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i + 1] && str[i] != '\"')
				i++;
		}
		if (ft_strrchr(delimiter, str[i]) || str[i + 1] == '\0')
			index++;
		i++;
	}
	return (index);
}

int	delimiter_found(char *str, char **pipe_split,
char delimiter, t_pipe_vars *p_vars)
{
	int	dif;
	int	k;

	if (p_vars->i == (int)(str_len(str)) - 1 && str[p_vars->i] == delimiter)
		return (0);
	dif = p_vars->i - p_vars->j;
	if (str[p_vars->i + 1] == '\0')
		dif = p_vars->i - p_vars->j + 1;
	k = 0;
	pipe_split[p_vars->index] = (char *)sf_malloc(dif + 1, ADD);
	while (k < dif)
		pipe_split[p_vars->index][k++] = str[p_vars->j++];
	pipe_split[p_vars->index][k] = '\0';
	p_vars->index++;
	return (1);
}

void	quotes_work(char *str, t_pipe_vars	*p_vars)
{
	if (str[p_vars->i] == '\'')
	{
		p_vars->i++;
		while (str[p_vars->i] && str[p_vars->i] != '\'')
			p_vars->i++;
	}
	else if (str[p_vars->i] == '\"')
	{
		p_vars->i++;
		while (str[p_vars->i] && str[p_vars->i] != '\"')
			p_vars->i++;
	}
}

char	**split_delimiter_func(char *str, char delimiter, char **pipe_split,
int *num_tab)
{
	t_pipe_vars	p_vars;

	p_vars.i = 0;
	p_vars.index = 0;
	p_vars.j = 0;
	*num_tab = calcul_delimiter(str, "|");
	pipe_split = sf_malloc(sizeof(char *) * (*num_tab + 1), ADD);
	while (str[p_vars.i])
	{
		quotes_work(str, &p_vars);
		if (str[p_vars.i] == delimiter || str[p_vars.i + 1] == '\0')
		{
			if (!delimiter_found(str, pipe_split, delimiter, &p_vars))
				return (NULL);
			p_vars.j = p_vars.i + 1;
		}
		p_vars.i++;
	}
	pipe_split[p_vars.index] = 0;
	return (pipe_split);
}

void	set_vars_check(t_pars_vars	*vars, T_STRING *str)
{
	vars->check = 0;
	skip_redi_spaces(vars, str);
	if (!vars->check)
		after_delimiter(vars, str);
}
