/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:01:45 by hmellahi          #+#    #+#             */
/*   Updated: 2021/08/12 20:56:46 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "parser.h"
# include "macros.h"
# include <sys/wait.h>
# include<signal.h> 
# include "functions.h"
# include <dirent.h>
# include "cmds.h"
# include "errors.h"
# include "vector.h"
# include "signals.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# define FREE 1
# define ADD 0
#endif
