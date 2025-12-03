/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkutlu <zkutlu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 01:24:38 by zkutlu            #+#    #+#             */
/*   Updated: 2025/06/29 01:28:41 by zkutlu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len = 1;
	if (n < 0)
	{
		n = n * (-1);
		len++;
	}
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		len;
	int		sign;

	sign = 1;
	len = ft_len(n);
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	if (n < 0)
		sign = -1;
	s[len] = '\0';
	while (len > 0)
	{
		s[len - 1] = 48 + sign * (n % 10);
		n = n / 10;
		len--;
	}
	if (sign == -1)
		s[0] = '-';
	return (s);
}
