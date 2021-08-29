/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_push_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:12:12 by hmellahi          #+#    #+#             */
/*   Updated: 2021/07/03 16:12:12 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	vector_push_back(t_vector *this, void *value)
{
	if (this->capacity <= this->size)
		vector_resize(this, this->capacity * 2);
	this->items[this->size++] = value;
}
