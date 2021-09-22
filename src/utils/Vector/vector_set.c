/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:44:00 by hmellahi          #+#    #+#             */
/*   Updated: 2021/09/20 18:44:00 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	vector_set(t_vector *this, int index, void *item)
{
	if (index >= 0 && index < this->size)
		this->items[index] = item;
}
