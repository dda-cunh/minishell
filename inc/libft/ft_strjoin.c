/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:28:46 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/04/14 14:04:56 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*concat;
	size_t	total_len;
	size_t	i;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	concat = (char *)malloc(total_len + 1);
	i = 0;
	if (!concat)
		return (NULL);
	while (*s1)
		concat[i++] = *s1++;
	while (*s2)
		concat[i++] = *s2++;
	concat[i] = '\0';
	return (concat);
}
