/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:09:39 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/04/14 14:54:35 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	sub_len;
	char	*sub_str;

	i = 0;
	if (*s == '\0' || start >= ft_strlen(s))
		sub_len = 1;
	else if (len > ft_strlen(s) - start)
		sub_len = ft_strlen(s) - start + 1;
	else
		sub_len = len + 1;
	sub_str = (char *)malloc(sub_len);
	if (!sub_str)
		return (NULL);
	while (start < ft_strlen(s) && --sub_len)
		sub_str[i++] = s[start++];
	sub_str[i] = '\0';
	return (sub_str);
}
