/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 23:14:54 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/04/12 16:55:51 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isformat(char a)
{
	if (a == ' ' || a == '\t' || a == '\f'
		|| a == '\r' || a == '\n' || a == '\v')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	int	sum;
	int	pol;

	pol = 1;
	sum = 0;
	while (isformat(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		if (*nptr++ == '-')
			pol = -1;
	while (ft_isdigit(*nptr))
		sum = sum * 10 + (*nptr++ - '0');
	return (pol * sum);
}
