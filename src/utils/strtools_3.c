/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtools_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 19:27:27 by hmellahi          #+#    #+#             */
/*   Updated: 2021/07/14 15:45:49 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	x;

	x = 0;
	while (s1[x] == s2[x] && s1[x] != '\0' && s2[x] != '\0')
		x++;
	return (s1[x] - s2[x]);
}

void	swap(t_string *xp, t_string *yp)
{
	t_string	temp;

	temp = *xp;
	*xp = *yp;
	*yp = temp;
}

t_bool	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
