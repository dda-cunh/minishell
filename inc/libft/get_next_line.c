/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:26:03 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/10 15:14:36 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*line;
	int			r;

	line = "";
	if (residual(buffer))
	{
		if (buff_endl(buffer))
			return (buffjoin(line, buffer, 0, -1));
		line = buffjoin(line, buffer, 0, -1);
	}
	r = 1;
	line = seek_line(buffer, line, r, fd);
	return (line);
}
