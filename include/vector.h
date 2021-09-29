/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:51:35 by hmellahi          #+#    #+#             */
/*   Updated: 2021/09/20 18:46:55 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# define VECTOR_INIT_CAPACITY 4
# define ADDRESS 1

typedef struct s_vector
{
	void	**items;
	int		capacity;
	int		size;
	int		tag;
}				t_vector;

void		new_vector(struct s_vector *this);
void		vector_push_back(t_vector *this, void *value);
void		vector_set(t_vector *this, int index, void *value);
void		*vector_get(t_vector *this, int index);
void		vector_delete(t_vector *this, int index);
void		vector_free(t_vector *this);
void		vector_resize(t_vector *this, int capacity);
int			vector_find(t_vector *this, T_STRING value);
T_STRING	*vector_to_array(t_vector *this);
t_vector	*vector_cpy(t_vector *this);

#endif