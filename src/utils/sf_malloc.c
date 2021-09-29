/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sf_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 16:00:45 by hamza             #+#    #+#             */
/*   Updated: 2021/09/29 14:36:27 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_all(t_vector *this)
{
	int	i;

	i = -1;
	while (++i < this->size)
		free(this->items[i]);
	free(this->items);
	return (NULL);
}

void	*sf_malloc(int size, int mode)
{
	void				*ptr;
	static t_vector		address;
	static int			k = 0;

	if (size <= 0)
		return (NULL);
	if (mode == FREE)
		return (free_all(&address));
	if (k++ == 0)
	{
		new_vector(&address);
		address.tag = ADDRESS;
	}
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	vector_push_back(&address, ptr);
	return (ptr);
}
