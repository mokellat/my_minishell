/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_resize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:15:52 by hmellahi          #+#    #+#             */
/*   Updated: 2021/07/03 16:15:52 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_realloc(void *ptr, size_t newsize)
{
	char	*newptr;
	size_t	cursize;

	if (ptr == 0)
		return (malloc(newsize));
	cursize = sizeof(ptr);
	if (newsize <= cursize)
		return (ptr);
	newptr = malloc(newsize);
	return (newptr);
}

void	vector_resize(t_vector *this, int capacity)
{
	void	**items;
	int		i;
	void	*tmp;

	if (this->tag == ADDRESS)
	{
		tmp = this->items;
		items = malloc(sizeof(void *) * capacity);
	}
	else
		items = sf_malloc(sizeof(void *) * capacity, ADD);
	i = -1;
	while (++i < this->size)
		items[i] = this->items[i];
	if (this->tag == ADDRESS)
		items[this->size++] = tmp;
	if (items)
	{
		this->items = items;
		this->capacity = capacity;
	}
}
