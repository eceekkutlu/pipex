/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkutlu <zkutlu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 04:53:41 by zkutlu            #+#    #+#             */
/*   Updated: 2025/06/25 18:35:14 by zkutlu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*dst;
	char	*sr;

	dst = (char *)dest;
	sr = (char *)src;
	if (sr < dst && dst < sr + n)
	{
		i = n;
		while (i > 0)
		{
			i--;
			dst[i] = sr[i];
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
