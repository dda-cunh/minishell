/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 22:17:26 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/04/11 22:36:54 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_bytes;
	unsigned char	*s2_bytes;

	s1_bytes = (unsigned char *)s1;
	s2_bytes = (unsigned char *)s2;
	if (!n)
		return (0);
	while (--n && *s1_bytes == *s2_bytes)
	{
		s1_bytes++;
		s2_bytes++;
	}
	return (*s1_bytes - *s2_bytes);
}
