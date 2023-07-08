/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_write_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 19:20:22 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/08 19:22:05 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_read_write_fd(int from_fd, int to_fd)
{
	char	*a;

	a = "";
	while (a)
	{
		a = get_next_line(from_fd);
		if (!a)
			break ;
		ft_putstr_fd(a, to_fd);
		free(a);
	}
	close(from_fd);
}
