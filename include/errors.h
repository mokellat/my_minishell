/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:13:55 by hmellahi          #+#    #+#             */
/*   Updated: 2021/08/12 22:29:40 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

enum	e_ERRORS
{
	TOO_MANY_ARGS,
	FILE_OR_DIR_NOT_FOUND,
	CMD_NOT_FOUND,
	PERMSSION_DENIED,
	IS_A_DIR,
	NUM_ARG_REQ,
	NOT_VALID_IDENT,
	OLDPWD_NOT_SET,
	SE_NEAR_RR,
	SE_NEAR_LR,
	SYNTAX_ERROR
};

#endif