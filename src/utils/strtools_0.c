/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtools_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:30:09 by hmellahi          #+#    #+#             */
/*   Updated: 2021/09/23 18:36:51 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_len(char *str)
{
	size_t	len;

	len = 0;
	while (*str && ++len)
		str++;
	return (len);
}

void	fput_char(char c, int fd)
{
	write(fd, &c, 1);
}

int	fput_str(char *str, int fd)
{
	write(fd, str, str_len(str));
	return (1);
}

void	put_char(char c)
{
	fput_char(c, 1);
}

void	put_str(char *str)
{
	fput_str(str, 1);
}
