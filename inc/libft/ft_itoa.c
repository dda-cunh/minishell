/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:22:34 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/04/14 15:45:11 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned char	a_len(long n)
{
	if (n == 0)
		return (1);
	return (1 + a_len(n / 10));
}

static	void	fill_a(char *a, long l, unsigned char len, int neg)
{
	if (neg)
		a[0] = '-';
	a[--len] = '\0';
	while (l)
	{
		a[--len] = (l % 10) + 48;
		l /= 10;
	}
}

char	*ft_itoa(int n)
{
	long			l;
	char			*a;
	int				neg;
	unsigned char	len;

	l = n;
	if (l == 0)
		return (ft_strdup("0"));
	len = a_len(l);
	neg = 0;
	if (l < 0)
	{
		l *= -1;
		len++;
		neg = 1;
	}
	a = (char *)malloc(len);
	if (!a)
		return (NULL);
	fill_a(a, l, len, neg);
	return (a);
}
