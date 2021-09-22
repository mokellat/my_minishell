/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_find.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:13:46 by hmellahi          #+#    #+#             */
/*   Updated: 2021/07/07 17:13:46 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	vector_find(t_vector *this, T_STRING value)
{
	int	i;

	i = -1;
	while (++i < this->size)
	{
		if (str_cmp(vector_get(this, i), value) == TRUE)
			return (i);
	}
	return (-1);
}
