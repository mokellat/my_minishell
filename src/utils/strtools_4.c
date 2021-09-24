/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtools_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 20:58:32 by hamza             #+#    #+#             */
/*   Updated: 2021/09/20 18:44:28 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*debut_tab(char const *s1, char const *set)
{
	char	*trim;
	char	*verif;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	trim = (char *)s1;
	verif = (char *)set;
	while (trim[i])
	{
		j = 0;
		while (verif[j])
		{
			if (trim[i] == verif[j])
			{
				i++;
				break ;
			}
			j++;
		}
		if (j == strlen(verif))
			break ;
	}
	return (&trim[i]);
}

static char	*fin_tab(char const *s1, char const *set)
{
	char	*trim;
	char	*verif;
	size_t	i;
	size_t	j;

	j = 0;
	i = strlen(s1) - 1;
	trim = (char *)s1;
	verif = (char *)set;
	while (trim[i])
	{
		j = 0;
		while (verif[j])
		{
			if (trim[i] == verif[j])
			{
				i--;
				break ;
			}
			j++;
		}
		if (j == strlen(verif))
			break ;
	}
	return (&trim[i + 1]);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	char	*ptr1;
	char	*trim;
	long	i;
	long	j;

	j = -1;
	i = 0;
	if (!s1 || !set)
		return (NULL);
	ptr = debut_tab(s1, set);
	if (!ptr[0])
		return (ft_strdup(ptr));
	ptr1 = fin_tab(s1, set);
	i = strlen(ptr) - strlen(ptr1);
	trim = (char *)sf_malloc((i + 1) * sizeof(char), ADD);
	if (!trim)
		return (NULL);
	while (++j < i)
		trim[j] = ptr[j];
	trim[j] = '\0';
	return (&trim[0]);
}

char	*ft_strdup(const char *src)
{
	char	*ptr;
	int		i;

	i = 0;
	while (src[i])
		i++;
	ptr = (char *)sf_malloc(sizeof(char) * (i + 1), ADD);
	if (!ptr)
		return (NULL);
	i = 0;
	while (src[i])
	{
		ptr[i] = src[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (str[i] == c)
			return ((char *)&str[i]);
		i--;
	}
	return (0);
}
