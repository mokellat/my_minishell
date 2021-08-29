/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 18:56:58 by mokellat          #+#    #+#             */
/*   Updated: 2021/07/29 16:12:34 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define t_string char*

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_split_pipe
{
	char            **pipe_str;
	int             num_tab;
}   t_split_pipe;

typedef struct s_file
{
	int		type;
	char	*name;
	char	is_quoted;
	int		fd;
}	t_file;

typedef struct s_pipeline
{
	char	**args;
	t_file	*files;
	int		files_count;
	int		n;
}	t_cmd;

int			ft_strcmp(char *s1, char *s2);
void		ft_putstr(char *s);
int			calcul_delimiter(char *str, char *delimiter);
char		**split_delimiter_func(char *str, char delimiter, char **pipe_split, int *num_tab);
t_cmd	*space_delimiter_func(char **str, char *delimiter, int num_strct);
int			multiple_red(char *str);
int			open_quotes(char *str);
t_string    expand(t_string str);
int			search_for_direction(char *str);
#endif
