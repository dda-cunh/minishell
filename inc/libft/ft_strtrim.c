/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:36:34 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/04/12 18:07:15 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set)
{
	while (*set)
		if (*set++ == c)
			return (1);
	return (0);
}

static size_t	len_trimmed(char const *s1, char const *set)
{
	size_t	len;

	while (*s1 && is_set(*s1, set))
		s1++;
	len = ft_strlen(s1);
	while (len > 0 && is_set(s1[len - 1], set))
		len--;
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	size_t	trim_len;
	size_t	i;

	i = 0;
	trim_len = len_trimmed(s1, set);
	trimmed = (char *)malloc(trim_len + 1);
	if (!trimmed)
		return (NULL);
	while (*s1 && is_set(*s1, set))
		s1++;
	while (i < trim_len)
		trimmed[i++] = *s1++;
	trimmed[i] = '\0';
	return (trimmed);
}
