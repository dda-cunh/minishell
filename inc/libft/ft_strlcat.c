/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 21:27:27 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/04/13 17:34:18 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	r;
	size_t	dst_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (!size)
		return (src_len);
	dst_len = ft_strlen(dst);
	if (dst_len >= size)
		return (size + src_len);
	dst += dst_len;
	r = dst_len + src_len;
	while ((dst_len < --size) && *src)
		*dst++ = *src++;
	*dst = '\0';
	return (r);
}
