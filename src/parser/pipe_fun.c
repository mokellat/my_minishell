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
			while (str[i + 1] && str[++i] != '\'');
		else if (str[i] == '\"')
			while (str[i + 1] && str[++i] != '\"');
		if (ft_strrchr(delimiter, str[i]) || str[i + 1] == '\0')
			index++;
		i++;
	}
	return (index);
}

void	delimiter_found(char *str, char **pipe_split, int i, char delimiter, int *index, int *j)
{
	int	dif;
	int	k;

	int length = str_len(str);
	if (i == length - 1 && str[i] == delimiter)
	{
		write(2, "syntax error\n", 14);
		exit(EXIT_FAILURE);
	}
	dif = i - *j;
	if (str[i + 1] == '\0')
		dif = i - *j + 1;
	k = 0;
	pipe_split[*index] = (char *)malloc(dif + 1);
	while (k < dif)
		pipe_split[*index][k++] = str[(*j)++];
	pipe_split[*index][k] = '\0';
	// *j = i + 1;
	(*index)++;
}

char	**split_delimiter_func(char *str, char delimiter, char **pipe_split, int *num_tab)
{
	int	i;
	int	index;
	int	j;

	i = 0;
	index = 0;
	j = 0;
	*num_tab = calcul_delimiter(str, "|");
	pipe_split = malloc(sizeof(char *) *  (*num_tab + 1));
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
		}
		if (str[i] == delimiter || str[i + 1] == '\0')
		{
			delimiter_found(str, pipe_split, i, delimiter, &index, &j);
			j = i + 1;
		}
		i++;
	}
	pipe_split[index] = 0;
	return (pipe_split);
}
