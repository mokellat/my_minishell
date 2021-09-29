/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtools_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 19:27:27 by hmellahi          #+#    #+#             */
/*   Updated: 2021/09/28 01:24:33 by hamza            ###   ########.fr       */
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

void	swap(T_STRING *xp, T_STRING *yp)
{
	T_STRING	temp;

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

char	**ft_reallocate(char **arr, int i)
{
	char		**new_map;
	int			j;

	j = 0;
	new_map = sf_malloc((i + 1) * sizeof(T_STRING), ADD);
	while (j < i)
	{
		new_map[j] = ft_strdup(arr[j]);
		j++;
	}
	new_map[j] = NULL;
	free(arr);
	return (new_map);
}
