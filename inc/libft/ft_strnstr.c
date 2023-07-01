/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 22:48:59 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/04/14 18:10:45 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*sol(const char	*big, const char *little, size_t len, size_t l_len)
{
	size_t	b_i;
	size_t	l_i;

	b_i = 0;
	l_i = 0;
	while (len > l_i && big[b_i + l_i])
	{
		if (big[b_i + l_i] == little[l_i])
		{
			l_i++;
		}
		else
		{
			len--;
			b_i++;
			l_i = 0;
		}
		if (l_i == l_len)
			return ((char *)(big + b_i));
	}
	return (NULL);
}

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	size_t	l_len;

	l_len = ft_strlen(little);
	if (!*little)
		return ((char *)big);
	return (sol(big, little, len, l_len));
}
