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

void	init_program(int i ,int *j, int *k, int *y, int *files_i, t_cmd *final_str, char **str)
{
	*j = 0;
	*k = 0;
	*y = 0;
	*files_i = 0;
	final_str[i].n = 1;
	final_str[i].args = malloc(sizeof(char *) * (final_str[i].n));
	final_str[i].files = malloc(sizeof(t_file) * 100);
	final_str[i].files_count = 0;
	str[i] = ft_strtrim(str[i], " ");
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
	x = 0; 
	final_str = malloc(sizeof(t_cmd) * num_strct);
	while (str[i])
	{
		init_program(i ,&j, &k, &y, &files_i, final_str, str);
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
				after_delimiter(str, &x, &dif, &k, i, &y, j, final_str);
			}
			j++;
		}
		check_redi_null(str, i, j);
		i++;
	}
	return (final_str);
}
