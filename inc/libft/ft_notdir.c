/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_notdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:31:48 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/11 16:03:09 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_notdir(char *path)
{
	int	tail;
	int	i;

	tail = 0;
	if (!path || !*path)
		return (NULL);
	i = -1;
	while (path[++i])
		;
	while (i > 0 && path[i - 1] == '/')
	{
		tail++;
		i--;
	}
	while (i > 0 && path[--i] != '/')
		;
	if (path[i] == '/')
		i++;
	return (ft_strdup_tail(&path[i], tail));
}
