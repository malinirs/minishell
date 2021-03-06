/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoods <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 11:05:08 by awoods            #+#    #+#             */
/*   Updated: 2021/11/12 18:09:33 by awoods           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *s, int start, int len)
{
	char	*str;
	int		i;
	int		len_s;

	i = 0;
	if (!s)
		return (NULL);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	len_s = ft_strlen(s);
	while (i < len && start <= len_s)
	{
		str[i] = s[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
