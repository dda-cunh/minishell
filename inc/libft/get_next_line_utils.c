/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:26:35 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/04/16 20:44:08 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	residual(char *buffer)
{
	int	i;

	i = -1;
	while (++i < BUFFER_SIZE)
		if (buffer[i])
			return (1);
	return (0);
}

int	buff_endl(char *buffer)
{
	int	i;

	i = -1;
	while (++i < BUFFER_SIZE)
		if (buffer[i] == '\n')
			return (1);
	return (0);
}

char	*seek_line(char *buffer, char *line, int r, int fd)
{
	while (r > 0)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r < 0)
		{
			if (*line)
				free(line);
			return (NULL);
		}
		if (r == 0 && !*line)
			return (NULL);
		if (buff_endl(buffer))
			return (buffjoin(line, buffer, 0, -1));
		line = buffjoin(line, buffer, 0, -1);
		if (!line)
			return (NULL);
	}
	return (line);
}

char	*alloc_concat(char *line, char *buff)
{
	char	*concat;
	size_t	i;
	size_t	j;
	size_t	l;

	i = 0;
	j = -1;
	l = 0;
	while (line[i])
		i++;
	while (++j < BUFFER_SIZE)
	{
		if (buff[j])
			l++;
		if (buff[j] == '\n')
			break ;
	}
	concat = malloc(i + l + 1);
	return (concat);
}

char	*buffjoin(char *line, char *buff, int i, int j)
{
	char		*concat;

	concat = alloc_concat(line, buff);
	if (!concat)
		return (NULL);
	while (*line)
		concat[i++] = *line++;
	if (*(line - i))
		free(line - i);
	while (++j < BUFFER_SIZE && buff[j] != '\n')
	{
		if (buff[j] && buff[j] != '\n')
			concat[i++] = buff[j];
		buff[j] = '\0';
	}
	if (j < BUFFER_SIZE && buff[j] == '\n')
	{
		buff[j] = '\0';
		concat[i++] = '\n';
	}
	concat[i] = '\0';
	return (concat);
}
