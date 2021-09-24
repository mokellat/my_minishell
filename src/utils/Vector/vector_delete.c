/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:13:23 by hmellahi          #+#    #+#             */
/*   Updated: 2021/07/07 17:13:23 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	vector_delete(t_vector *this, int index)
{
	int		i;
	void	**new_arr;
	int		j;

	j = 0;
	i = -1;
	new_arr = sf_malloc(sizeof(void *) * 300, ADD);
	while (++i < this->size)
	{
		if (i != index)
			new_arr[i - j] = this->items[i];
		else
			j = 1;
	}
	new_arr[i] = NULL;
	this->items = new_arr;
	this->size--;
}
