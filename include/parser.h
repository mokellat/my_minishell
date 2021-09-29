/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:30:31 by hmellahi          #+#    #+#             */
/*   Updated: 2021/09/20 18:30:31 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define T_STRING char*

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_split_pipe
{
	char	**pipe_str;
	int		num_tab;
}	t_split_pipe;

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
	int		is_empty_string_quoted;
	int		index;
}	t_cmd;

typedef struct s_pars_vars
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
	int		check;
	int		name_is_quoted;
	int		is_quoted;
	char	*arg;
}	t_pars_vars;

typedef struct s_pipe_vars_
{
	int	i;
	int	index;
	int	j;
}	t_pipe_vars;

int			ft_strcmp(char *s1, char *s2);
void		ft_putstr(char *s);
int			calcul_delimiter(char *str, char *delimiter);
char		**split_delimiter_func(char *str, char delimiter,
				char **pipe_split, int *num_tab);
t_cmd		*space_delimiter_func(char **str, char *delimiter, int num_strct);
int			multiple_red(char *str);
int			open_quotes(char *str);
T_STRING	expand(T_STRING str);
int			search_for_direction(char *str);
void		redirections(t_pars_vars *pars_vars, char **str);
void		quoted(t_pars_vars *pars_vars, char **str);
void		is_quoted_assign(t_pars_vars *pars_vars, char **str);
void		skip_quotes(t_pars_vars *pars_vars, char **str);
void		args_and_expand(t_pars_vars *pars_vars, char **str);
char		inside_single_quotes(char *str);
int			before_delimiter(t_pars_vars *pars_vars, char **str);
void		after_delimiter(t_pars_vars *pars_vars, char **str);
int			check_redi_null(t_pars_vars *pars_vars, char **str);
void		check_name_after(char **str, t_pars_vars *vars);
void		assign_name_after(char **str, t_pars_vars *vars);
void		set_vars_check(t_pars_vars	*vars, T_STRING *str);
void		skip_redi_spaces(t_pars_vars *vars, char **str);
int			is_quote(int c);
T_STRING	custom_substr(T_STRING str, int start, int end, int is_single);
void		args_expand_exec(t_pars_vars *vars, char **str,
				int *start, int *end);
#endif
