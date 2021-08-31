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
	int		index;
	t_cmd	*final_str;
	int		redi_lenght;
	int		redi_index;
	int		files_i;

	i = 0;
	j = 0;
	index = 0;
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
		final_str[index].n = 1;
		final_str[index].args = malloc(sizeof(char *) * (final_str[index].n));
		final_str[index].files = malloc(sizeof(t_file) * 100);
		final_str[index].files_count = 0;
		str[i] = ft_strtrim(str[i], " ");
		while (j < (int)str_len(str[i]))
		{
			if (j > 0 && (str[i][j - 1] == '>' || str[i][j - 1] == '<'))
			{
				j--;
				if (str[i][j] == '>')
					final_str[index].files[files_i].type = RED_OUT;
				else if (str[i][j] == '<')
					final_str[index].files[files_i].type = RED_IN;
				j++;
				if (str[i][j] == '>')
				{
					final_str[index].files[files_i].type = RED_OUT_AP;
					j++;
				}
				else if (str[i][j] == '<')
				{
					final_str[index].files[files_i].type = RED_IN_SOURCE;
					j++;
				}
				while (str[i][j] && str[i][j] == ' ')
					j++;
				if (str[i][j] && (str[i][j] == '\'' || str[i][j] == '\"'))
				{
					if (str[i][j] == '\'')
						final_str[index].files[files_i].is_quoted
							= SINGLE_QUOTE;
					else if (str[i][j] == '\"')
						final_str[index].files[files_i].is_quoted
							= DOUBLE_QUOTE;
					j++;
					redi_lenght = j;
					while (str[i][redi_lenght] && str[i][redi_lenght] != '\'')
						redi_lenght++;
				}
				else
				{
					redi_lenght = j;
					final_str[index].files[files_i].is_quoted = 0;
					while (str[i][redi_lenght] && str[i][redi_lenght] != ' ')
						redi_lenght++;
				}
				final_str[index].files[files_i].name
					= malloc(redi_lenght - j + 2);
				redi_lenght = 0;
				if (final_str[index].files[files_i].is_quoted)
				{
					if (final_str[index].files[files_i].is_quoted
						== SINGLE_QUOTE)
					{
						while (str[i][j] && str[i][j] != '\'')
							final_str[index].files[files_i].name[redi_lenght++]
								= str[i][j++];
					}
					else if (final_str[index].files[files_i].is_quoted
						== DOUBLE_QUOTE)
					{
						while (str[i][j] && str[i][j] != '\"')
							final_str[index].files[files_i].name[redi_lenght++]
								= str[i][j++];
					}
					j++;
				}
				else
				{
					while (str[i][j] && str[i][j] != ' ')
						final_str[index].files[files_i].name[redi_lenght++]
							= str[i][j++];
				}
				if (!ft_strcmp(final_str[index].files[files_i].name, "\0"))
				{
					write(2, "syntax error\n", 14);
					exit(EXIT_FAILURE);
				}
				final_str[index].files[files_i].name[redi_lenght] = 0;
				final_str[index].files[files_i].name
					= ft_strtrim(final_str[index].files[files_i].name, "\'\"");
				files_i++;
				final_str[index].files_count++;
			}
			if (str[i][j] == '\'')
			{
				j++;
				while (str[i][j] && str[i][j] != '\'')
					j++;
			}
			else if (str[i][j] == '\"')
			{
				j++;
				while (str[i][j] && str[i][j] != '\"')
					j++;
			}
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
					final_str[index].n++;
					final_str[index].args = realloc(final_str[index].args,
							sizeof(char *) * (final_str[index].n));
				}
				final_str[index].args[y] = (char *)malloc(dif + 1);
				while (x < dif)
				{
					if (k != 0 && str[i][k] && str[i][k] == '\'')
					{
						dif--;
						k++;
					}
					else
						final_str[index].args[y][x++] = str[i][k++];
				}
				final_str[index].args[y][x] = '\0';
				if (!inside_single_quotes(final_str[index].args[y]))
					final_str[index].args[y]
						= expand(ft_strtrim(final_str[index].args[y], "\'\""));
				else
					final_str[index].args[y]
						= ft_strtrim(final_str[index].args[y], "\'\"");
				k = j + 1;
				x = 0;
				y++;
			}
			j++;
		}
		if (j > 0 && (str[i][j - 1] == '>' || str[i][j - 1] == '<'))
		{
			write(2, "syntax error\n", 14);
			exit(EXIT_FAILURE);
		}
		index++;
		i++;
	}
	return (final_str);
}
