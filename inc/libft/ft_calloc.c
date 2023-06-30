/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:44:34 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/04/12 17:59:44 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*bytes;
	size_t			total_bytes;

	total_bytes = size * nmemb;
	bytes = (unsigned char *)malloc(total_bytes);
	if (!bytes)
		return (NULL);
	ft_bzero(bytes, total_bytes);
	return (bytes);
}
