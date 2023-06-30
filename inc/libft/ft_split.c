/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:05:30 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/04/14 15:27:42 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	n_strings(char const *s, char c)
{
	int	i;
	int	n;
	int	start;

	n = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (s[start])
			n++;
	}
	return (n);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		start;
	char	**sep;

	sep = (char **)malloc(sizeof(char *) * (n_strings(s, c) + 1));
	if (!sep)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (s[start])
			sep[j++] = ft_substr(s, start, i - start);
	}
	sep[j] = NULL;
	return (sep);
}
