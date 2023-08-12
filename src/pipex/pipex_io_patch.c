/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_io_patch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmouronh <fmouronh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 21:16:37 by fmouronh          #+#    #+#             */
/*   Updated: 2023/08/12 21:16:47 by fmouronh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_interrupt(char *line, bool sigint)
{
	if (!line)
		ft_putendl_fd("warning: here-document delimited by end-of-file", 2);
	else if (line && sigint)
		free(line);
}
