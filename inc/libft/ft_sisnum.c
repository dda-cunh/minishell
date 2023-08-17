/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sisnum.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 11:47:05 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/08/17 11:47:14 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sisnum(const char *s)
{
	int	ran;

	ran = 0;
	if (s)
	{
		if (*s == '+' || *s == '-')
			s++;
		while (*s)
		{
			ran = 1;
			if (!ft_isdigit(*s++))
				return (0);
		}
		if (ran)
			return (1);
	}
	return (0);
}
