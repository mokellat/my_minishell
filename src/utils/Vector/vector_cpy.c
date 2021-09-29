/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_cpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 19:56:44 by hamza             #+#    #+#             */
/*   Updated: 2021/07/03 16:19:59 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vector	*vector_cpy(t_vector *this)
{
	t_vector	*cpy;
	int			i;

	i = -1;
	cpy = sf_malloc(sizeof(t_vector), ADD);
	cpy->items = sf_malloc(sizeof(void *) * this->capacity, ADD);
	cpy->size = this->size;
	while (++i < this->size)
		cpy->items[i] = str_dup(this->items[i]);
	return (cpy);
}
