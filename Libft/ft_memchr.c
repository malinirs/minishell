/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoods <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:32:02 by awoods            #+#    #+#             */
/*   Updated: 2021/11/12 18:09:33 by awoods           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t	n)
{
	int					i;
	const unsigned char	*str;
	unsigned char		c_2;

	i = 0;
	str = (const unsigned char *)s;
	c_2 = (unsigned char)c;
	while (n > 0)
	{
		if (str[i] == c_2)
			return ((void *)(str + i));
		i++;
		n--;
	}
	return (NULL);
}
