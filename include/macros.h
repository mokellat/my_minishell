/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:48:31 by hmellahi          #+#    #+#             */
/*   Updated: 2021/08/13 16:47:32 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define SHELL_NAME "minishell\n"
# define FALSE          0
# define TRUE           1
# define NOT            !
# define AND            &&
# define OR             ||
# define ELIF           else if // why not?
# define FAIL           0
# define UNCOMPLETED    1
# define STDIN          0
# define STDOUT         1
# define DEBUG_MODE     1
# define STATUS         1
# define OUTPUT         0
# define CMDS_COUNT     7
# define RED_IN         0
# define RED_OUT        1
# define RED_OUT_AP     2
# define RED_IN_SOURCE  3
# define EOL            '\n'
# define EMPTY          0
# define NOT_FOUND 1
# define UNQUOTED       0
# define SINGLE_QUOTE   1
# define DOUBLE_QUOTE   2

typedef char	t_bool;

#endif
