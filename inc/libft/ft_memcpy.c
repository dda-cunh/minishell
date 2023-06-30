/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:38:40 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/04/12 18:42:19 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

void	*ft_memcpy(void *restrict dest, const void *restrict src, size_t n)
{
	unsigned char	*src_bytes;
	unsigned char	*dest_bytes;

	src_bytes = (unsigned char *)src;
	dest_bytes = (unsigned char *)dest;
	if (dest_bytes >= src_bytes && dest_bytes <= src_bytes + n)
		return (ft_memmove(dest, src, n));
	while (n--)
		*dest_bytes++ = *src_bytes++;
	return (dest);
}
