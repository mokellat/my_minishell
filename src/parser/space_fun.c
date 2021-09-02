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

t_cmd	*space_delimiter_func(char **str, char *delimiter, int num_strct)
{
	int		i;
	int		j;
	int		dif;
	int		k;
	int		x;
	int		y;
	t_cmd	*final_str;
	int		redi_lenght;
	int		files_i;

	i = 0;
	j = 0;
	k = 0;
	x = 0;
	y = 0;
	final_str = malloc(sizeof(t_cmd) * num_strct);
	while (str[i])
	{
		j = 0;
		k = 0;
		y = 0;
		files_i = 0;
		final_str[i].n = 1;
		final_str[i].args = malloc(sizeof(char *) * (final_str[i].n));
		final_str[i].files = malloc(sizeof(t_file) * 100);
		final_str[i].files_count = 0;
		str[i] = ft_strtrim(str[i], " ");
		while (j < (int)str_len(str[i]))
		{
			before_delimiter(str, &j, final_str, i, &files_i, &redi_lenght);
			if (str[i][j] && (ft_strrchr(delimiter, str[i][j])
				|| str[i][j + 1] == '\0'))
			{
				if (k > 0 && (str[i][k - 1] == '>' || str[i][k - 1] == '<'))
				{
					j++;
					k = j;
					continue ;
				}
				if (str[i][k] == ' ')
				{
					while (str[i][k] && str[i][k] == ' ')
						k++;
					j = k;
					continue ;
				}
				dif = j - k;
				if ((str[i][k] == '>' || str[i][k] == '<'))
				{
					j++;
					k++;
					continue ;
				}
				if (str[i][j + 1] == '\0')
					dif = j - k + 1;
				if (y > 0)
				{
					final_str[i].n++;
					final_str[i].args = realloc(final_str[i].args,
							sizeof(char *) * (final_str[i].n));
				}
				final_str[i].args[y] = (char *)malloc(dif + 1);
				args_and_expand(str, &x, &dif, &k, i, &y, j, final_str);
			}
			j++;
		}
		if (j > 0 && (str[i][j - 1] == '>' || str[i][j - 1] == '<'))
		{
			write(2, "syntax error\n", 14);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (final_str);
}
