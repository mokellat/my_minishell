/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvjn <marvjn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 16:08:32 by marvjn            #+#    #+#             */
/*   Updated: 2020/04/03 16:08:32 by marvjn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_vector(t_vector *this)
{
	static int	j = 0;

	this->tag = 0;
	this->capacity = 4;
	this->size = 0;
	if (j == 0)
	{
		this->items = malloc(sizeof(void *) * this->capacity);
		j++;
	}
	else
		this->items = sf_malloc(sizeof(void *) * this->capacity, ADD);
}
