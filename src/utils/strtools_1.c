/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtools_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:34:41 by hmellahi          #+#    #+#             */
/*   Updated: 2021/09/20 18:46:55 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*char_addr(char c, char *buff)
{
	while (*buff)
	{
		if (*buff == c)
			return (buff);
		buff++;
	}
	return (NULL);
}

t_bool	str_cmp(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;

	if (s1 == NULL && s2 == NULL)
		return (1);
	if (s1 == NULL || s2 == NULL)
		return (0);
	len1 = str_len(s1);
	len2 = str_len(s2);
	if (len1 != len2)
		return (0);
	len1++;
	while (len1--)
		if (s1[len1] != s2[len1])
			return (0);
	return (1);
}

int	ft_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c <= 122))
		return (1);
	return (0);
}

int	tablen(T_STRING *taab)
{
	int	i;

	i = -1;
	while (taab[++i])
		;
	return (i);
}
