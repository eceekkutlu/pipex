/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkutlu <zkutlu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 00:18:22 by zkutlu            #+#    #+#             */
/*   Updated: 2025/06/29 03:42:18 by zkutlu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*array;

	array = (char *)s;
	i = ft_strlen(array);
	while (i > 0)
	{
		if (array[i - 1] == (char)c)
			return ((array + i - 1));
		i--;
	}
	if ((char)c == '\0')
		return (array + ft_strlen(array));
	return (NULL);
}
