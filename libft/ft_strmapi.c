/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkutlu <zkutlu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:29:50 by zkutlu            #+#    #+#             */
/*   Updated: 2025/06/28 19:46:09 by zkutlu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		len;
	char	*str1;

	i = 0;
	if (!s ||!f)
		return (NULL);
	len = ft_strlen(s);
	str1 = malloc(sizeof(char) * (len + 1));
	if (!str1)
		return (NULL);
	while (i < len)
	{
		str1[i] = f(i, s[i]);
		i++;
	}
	str1[i] = '\0';
	return (str1);
}
