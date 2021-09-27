/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:03:46 by mokellat          #+#    #+#             */
/*   Updated: 2021/07/29 15:51:07 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redi_exec_exec(int i, char *str, int *index)
{
	if (str[i] == '>' || str[i] == '<')
	{
		i++;
		if (str[i] == ' ' && str[i])
		{
			while (str[i] && str[i] == ' ')
				i++;
			if (str[i] == '>' || str[i] == '<')
				return (0);
			return (1);
		}
		while ((str[i] == '>' || str[i] == '<'))
		{
			i++;
			(*index)++;
		}
	}
	return (1);
}

int	redi_exec(int i, char *str, int *index)
{
	while (++i < (int)strlen(str))
	{
		if (str[i] == '>' && str[i + 1] == '<')
			return (0);
		if (str[i] == '<' && str[i + 1] == '>')
			return (0);
		if (!redi_exec_exec(i, str, index))
			return (0);
		if (*index == 1)
		{
			while (str[i] && ft_isalpha(str[i]))
				i++;
			if (str[i] && str[i] == ' ')
				(*index) = 0;
		}
	}
	return (1);
}

int	multiple_red(char *str)
{
	int	i;
	int	index;

	i = -1;
	index = 0;
	if (!redi_exec(i, str, &index))
		return (0);
	if (index > 1)
		return (0);
	else
		return (1);
	return (1);
}

int	open_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (!str[i])
				return (0);
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			if (!str[i])
				return (0);
		}
	}
	return (1);
}
