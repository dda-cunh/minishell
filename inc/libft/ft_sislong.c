/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sislong.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 11:45:36 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/08/17 11:57:45 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sislong(const char *s)
{
	int		slen;
	char	pre;

	if (s)
	{
		if (!ft_sisnum(s))
			return (0);
		pre = '\0';
		if (*s == '+' || *s == '-')
			pre = *s++;
		slen = ft_strlen(s);
		if (slen > 20 || slen < 1)
			return (0);
		if (slen == 19)
		{
			if ((!pre || pre == '+')
				&& ft_strncmp(s, "9223372036854775807", 20) > 0)
				return (0);
			if (pre == '-' && (ft_strncmp(s, "9223372036854775808", 20) > 0))
				return (0);
		}
		return (1);
	}
	return (0);
}
