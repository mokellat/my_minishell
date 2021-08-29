/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:14:07 by hmellahi          #+#    #+#             */
/*   Updated: 2021/07/07 17:14:07 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*vector_get(t_vector *this, int index)
{
	if (index >= 0 && index < this->size)
		return (this->items[index]);
	return (NULL);
}
