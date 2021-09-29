/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtools_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 10:02:05 by hmellahi          #+#    #+#             */
/*   Updated: 2021/09/29 10:02:39 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_dup(char *str)
{
	size_t			i;
	size_t			len;
	char			*dup;

	len = str_len(str);
	dup = (char *)sf_malloc(len + 1, ADD);
	if (!dup)
		return (0);
	dup[len] = 0;
	i = -1;
	while (++i < len)
		dup[i] = str[i];
	return (dup);
}

char	*join(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	l;
	char			*s3;

	if (!s1 || !s2)
		return (NULL);
	i = str_len(s1) + str_len(s2);
	s3 = (char *)sf_malloc((i + 1) * sizeof(char), ADD);
	if (!s3)
		return (NULL);
	s3[i] = '\0';
	i = 0;
	while (s1[i] != 0)
	{
		s3[i] = s1[i];
		i++;
	}
	l = 0;
	while (s2[l])
	{
		s3[i++] = (char)s2[l];
		l++;
	}
	return (s3);
}

char	*sub_str(char *s, size_t start, size_t len)
{
	unsigned int	i;
	unsigned int	slen;
	char			*s2;

	if (!s)
		return (NULL);
	slen = str_len(s);
	if (start > slen)
		return (str_dup(""));
	if (len > slen)
		len = slen;
	s2 = (char *)sf_malloc((len + 1) * sizeof(char), ADD);
	if (!s2)
		return (NULL);
	i = 0;
	while (i < len && s[start])
		s2[i++] = s[start++];
	s2[i] = '\0';
	return (s2);
}

T_STRING	cpy_from_to(T_STRING	ptr1,	T_STRING	ptr2)
{
	T_STRING	str;
	int			i;
	int			len;

	len = -1;
	while ((ptr1 + ++len) != ptr2)
		;
	str = sf_malloc(len + 1, ADD);
	i = -1;
	while (++i < len)
		str[i] = ptr1[i];
	str[i] = 0;
	return (str);
}

char	*join_c(char *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i])
		i++;
	str = (char *)sf_malloc(i + 2, ADD);
	if (!str)
		return (0);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	return (str);
}
