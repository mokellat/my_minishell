/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:02:21 by hmellahi          #+#    #+#             */
/*   Updated: 2021/09/29 10:53:49 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H
# include "minishell.h"
# include "vector.h"
# include "cmds.h"

typedef struct s_redir
{
	int	in_file;
	int	out_file;
	int	err;
}				t_redir;

T_STRING	*init_errs_msgs(void);
void		init_shell(t_shell *shell, T_STRING *env_vars);
int			is_directory(T_STRING path);
int			parse(T_STRING line, t_cmd **cmds);
void		shell_loop(t_shell *shell);
void		handle_error(T_STRING error);
void		handle_signal(int event_code);
int			str_len(char *str);
void		put_char(char c);
void		put_str(char *str);
void		fput_char(char c, int fd);
int			fput_str(char *str, int fd);
int			handle_ctrl_c(T_STRING *line, t_shell *shell);
t_bool		str_cmp(char *s1, char *s2);
void		swap(T_STRING *xp, T_STRING *yp);
int			ft_strcmp(char *s1, char *s2);
char		*ft_itoa(unsigned long long n);
char		*str_dup(char *str);
char		*join(char *s1, char *s2);
char		*sub_str(char *s, size_t start, size_t len);
T_STRING	cpy_from_to(T_STRING ptr1, T_STRING ptr2);
T_STRING	expand(T_STRING str);
char		*char_addr(char c, char *buff);
int			get_line(int fd, char **line);
char		**split(char const *s, char c);
void		init_env(t_env *env, T_STRING *env_vars);
T_STRING	get_env(t_shell *shell, T_STRING var_key);
int			print_err(T_STRING path, int error_index);
t_res		fork_pipes(int n, t_cmd *cmd, t_shell *shell);
int			shell_launch(t_shell *shell, T_STRING *args);
t_res		execute_builtin_cmd(t_cmd cmd,
				t_shell *shell, int *is_builtin);
char		*join_c(char *s, char c);
char		editorReadKey(void);
void		enableRawMode(void);
t_bool		is_digit(char c);
int			ft_isalpha(int c);
int			tablen(T_STRING *taab);
T_STRING	validate_identifier(T_STRING ident, T_STRING cmd);
t_redir		check_for_redirections(t_cmd *cmd);
int			red_in_source(t_file *file);
T_STRING	*env_to_arr(t_env *env, int flag);
void		*sf_malloc(int size, int mode);
t_shell		*shell_ref(t_shell *shell);
char		*ft_strdup(const char *src);
char		*ft_strrchr(const char *str, int c);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_reallocate(char **arr, int i);
void		expand_and_delete_garbage(T_STRING *line);
void		name_it(int n, t_cmd *cmd, t_shell *shell, t_res *res);
void		close_all_pipes(int **fd, int n);
int			run_heredoc(T_STRING *line, T_STRING *buff,
				T_STRING source, char is_quoted);
#endif