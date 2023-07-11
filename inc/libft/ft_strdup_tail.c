/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_tail.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:03:26 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/11 16:03:46 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_tail(const char *s, int tail)
{
	size_t	s_len;
	char	*dup;

	s_len = ft_strlen(s) - tail;
	dup = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, s_len);
	dup[s_len] = '\0';
	return (dup);
}
