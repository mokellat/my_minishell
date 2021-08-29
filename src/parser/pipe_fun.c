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
	while(str[i])
	{
		if(str[i] == '\'')
			while(str[i + 1] && str[++i] != '\'');
		else if(str[i] == '\"')
			while(str[i + 1] && str[++i] != '\"');
		if(ft_strrchr(delimiter, str[i]) || str[i + 1] == '\0')
			index++;
		i++;
	}
	return (index);
}

char	**split_delimiter_func(char *str, char delimiter, char **pipe_split, int *num_tab)
{
	int	i;
	int	k;
	int	dif;
	int	index;
	int	j;

	i = 0;
	j = 0;
	index = 0;
	*num_tab = calcul_delimiter(str, "|");
	pipe_split = malloc(sizeof(char *) *  (*num_tab + 1));
	while(str[i])
	{
		if(str[i] == '\'')
			while(str[++i] != '\'');
		else if(str[i] == '\"')
			while(str[++i] != '\"');
		if(str[i] == delimiter || str[i + 1] == '\0')
		{
			if(i = 0 && str[i] == delimiter)
			{
				write(2, "syntax error\n", 14);
				return (0);
			}
			dif = i - j;
			if(str[i + 1] == '\0')
				dif = i - j + 1;
			if(str[i] == '\'')
				dif -= 1;
			k = 0;
			pipe_split[index] = (char *)malloc(dif + 1);
			while(k < dif)
				pipe_split[index][k++] = str[j++];
			pipe_split[index][k] = '\0';
			j = i + 1;
			index++;
		}
		i++;
	}
	pipe_split[index] = 0;
	return (pipe_split);
}
