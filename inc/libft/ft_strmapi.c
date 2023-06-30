/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:13:56 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/04/12 15:27:01 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*mapped;

	mapped = (char *)malloc(ft_strlen(s) + 1);
	if (!mapped)
		return (NULL);
	i = -1;
	while (s[++i])
		mapped[i] = f(i, s[i]);
	mapped[i] = '\0';
	return (mapped);
}
