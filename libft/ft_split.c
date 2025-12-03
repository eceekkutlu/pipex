/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkutlu <zkutlu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:55:57 by zkutlu            #+#    #+#             */
/*   Updated: 2025/06/29 03:21:01 by zkutlu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	int	in_word;
	int	count;

	in_word = 0;
	count = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c && in_word == 1)
			in_word = 0;
		s++;
	}
	return (count);
}

static void	*free_all(char **arr, size_t i)
{
	while (i--)
		free(arr[i]);
	free (arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	i;
	size_t	j;
	size_t	len;

	len = count_words(s, c);
	i = 0;
	result = malloc(sizeof(char *) * (len + 1));
	if (!result)
		return (NULL);
	while (i < len)
	{
		while (*s == c)
			s++;
		j = 0;
		while (s[j] != c && s[j])
			j++;
		result[i] = ft_substr(s, 0, j);
		s += j;
		if (!result[i])
			return (free_all(result, i));
		i++;
	}
	result[i] = NULL;
	return (result);
}
