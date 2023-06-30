/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 22:07:28 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/04/12 19:41:07 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_bytes;

	s_bytes = (unsigned char *)s;
	while (n--)
	{
		if (*s_bytes == (unsigned char)c)
			return (s_bytes);
		s_bytes++;
	}
	return (NULL);
}
