/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_write_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 19:20:22 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/22 23:03:43 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_read_write_fd(int from_fd, int to_fd, int close_from, int close_to)
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
	if (close_from)
		close(from_fd);
	if (close_to)
		close(to_fd);
	return ;
}
