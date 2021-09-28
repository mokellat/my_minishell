/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:25:50 by hmellahi          #+#    #+#             */
/*   Updated: 2021/09/27 20:38:34 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long	ft_digitnb(unsigned long long n)
{
	long		size;

	if (n == 0)
		return (1);
	size = 0;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size++);
}

static int	ft_sign(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

char	*ft_itoa(unsigned long long n)
{
	long		n_long;
	long		length;
	char		*fresh;

	n_long = n;
	length = ft_digitnb(n_long);
	fresh = (char *)sf_malloc((length + 1) * sizeof(char), ADD);
	if (!fresh)
		return (NULL);
	fresh[length] = '\0';
	length--;
	if (n_long < 0)
		n_long = -n_long;
	while (length >= 0)
	{
		fresh[length] = (n_long % 10) + '0';
		length--;
		n_long /= 10;
	}
	if (ft_sign(n))
		fresh[0] = '-';
	return (fresh);
}
