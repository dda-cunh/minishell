/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:48:43 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/04/12 18:48:02 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*src_bytes;
	unsigned char	*dest_bytes;

	i = -1;
	src_bytes = (unsigned char *)src;
	dest_bytes = (unsigned char *)dest;
	if (dest_bytes >= src_bytes && dest_bytes <= src_bytes + n)
	{
		if (dest)
			while (n--)
				dest_bytes[n] = src_bytes[n];
	}
	else
		while (++i < n)
			dest_bytes[i] = src_bytes[i];
	return (dest);
}
