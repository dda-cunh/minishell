/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 21:39:07 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/04/14 14:00:02 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (*(s + i) && *(s + i) != (char)c)
		i++;
	if (*(s + i) == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	int		bad = 0;
	char	*str = "teste";
	char	*empty = "";

	printf("NON EMPTY\n\tSTART:\t%p\n", str);
	for (int i = -20; i <= 200; i++)
	{
		if (ft_strchr(str, i) != strchr(str, i))
		{
			bad = 1;
			printf("\tError with i = %d\n", i);
		}
	}
	if (!bad)
		printf("\tOK\n");
	bad = 0;
	printf("EMPTY\n\tSTART:\t%p\n", empty);
	for (int i = -20; i <= 200; i++)
	{
		if (ft_strchr(empty, i) != strchr(empty, i))
		{
			bad = 1;
			printf("\tError with i = %d\n", i);
		}
	}
	if (!bad)
		printf("\tOK\n");
}
*/