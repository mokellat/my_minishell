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
t_cmd		*space_delimiter_func(char **str, char *delimiter, int num_strct);
int			multiple_red(char *str);
int			open_quotes(char *str);
t_string    expand(t_string str);
int			search_for_direction(char *str);
void    	redirections(int i, int *j, char **str, t_cmd *final_str, int files_i);
void    	quoted(char **str, int i, int *j, t_cmd *final_str, int files_i, int *redi_lenght);
void		is_quoted_assign(char **str, int i, int *j, t_cmd *final_str, int *redi_lenght, int files_i);
void		skip_quotes(char **str, int i, int *j);
void		args_and_expand(char **str, int *x, int *dif, int *k, int i, int *y, int j,t_cmd *final_str);
char		inside_single_quotes(char *str);
void    	before_delimiter(char **str, int *j, t_cmd *final_str, int i, int *files_i, int *redi_lenght);
void		after_delimiter(char **str, int *x, int *dif, int *k, int i, int *y, int j,t_cmd *final_str);
void		check_redi_null(char **str, int i, int j);
#endif
