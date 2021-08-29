/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:02:21 by hmellahi          #+#    #+#             */
/*   Updated: 2021/08/12 21:22:37 by hamza            ###   ########.fr       */
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

t_string	*init_errs_msgs(void);
void		init_shell(t_shell *shell, t_string *env_vars);
int			is_directory(t_string path);
int			parse(t_string line, t_cmd **cmds);
void		shell_loop(t_shell *shell);
void		handle_error(t_string error);
void		handle_signal(int event_code);
size_t		str_len(char *str);
void		put_char(char c);
void		put_str(char *str);
void		fput_char(char c, int fd);
int			fput_str(char *str, int fd);
int			handle_ctrl_c(t_shell *shell);
t_bool		str_cmp(char *s1, char *s2);
void		swap(t_string *xp, t_string *yp);
int			ft_strcmp(char *s1, char *s2);
char		*ft_itoa(unsigned long long n);
char		*str_dup(char *str);
char		*join(char *s1, char *s2);
char		*sub_str(char *s, size_t start, size_t len);
t_string	cpy_from_to(t_string ptr1, t_string ptr2);
t_string	expand(t_string str);
char		*char_addr(char c, char *buff);
int			get_line(int fd, char **line);
char		**split(char const *s, char c);
void		init_env(t_env *env, t_string *env_vars);
t_string	get_env(t_shell *shell, t_string var_key);
int			print_err(t_string path, int error_index);
t_res		fork_pipes(int n, t_cmd *cmd, t_shell *shell);
int			shell_launch(t_shell *shell, t_string *args);
t_res		execute_builtin_cmd(t_string *args,
				t_shell *shell, int *is_builtin);
char		*join_c(char *s, char c);
char		editorReadKey(void);
void		enableRawMode(void);
t_bool		is_digit(char c);
int			ft_isalpha(int c);
int			tablen(t_string *taab);
t_string	validate_identifier(t_string ident, t_string cmd);
t_redir		check_for_redirections(t_cmd *cmd);
int			red_in_source(t_file *file);
t_string	*env_to_arr(t_env *env);
void		*sf_malloc(int size, int mode);
t_shell		*shell_ref(t_shell *shell);
char		*ft_strdup(const char *src);
char	*ft_strrchr(const char *str, int c);
char	*ft_strtrim(char const *s1, char const *set);
#endif