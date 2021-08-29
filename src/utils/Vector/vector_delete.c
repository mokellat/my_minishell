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
	int	i;

	i = -1;
	if (index < 0 || index >= this->size)
		return ;
	this->items[index] = NULL;
	while (++i < this->size - 1)
	{
		this->items[i] = this->items[i + 1];
		this->items[i + 1] = NULL;
	}
	this->size--;
	if (this->size > 0 && this->size == this->capacity / 4)
		vector_resize(this, this->capacity / 2);
}
