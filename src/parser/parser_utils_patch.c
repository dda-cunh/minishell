/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_patch.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmouronh <fmouronh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:26:00 by fmouronh          #+#    #+#             */
/*   Updated: 2023/08/12 20:26:08 by fmouronh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*trim_file_quotes(char *file, char quote)
{
	char	*trimmed;

	trimmed = ft_strtrim(file, &quote);
	free(file);
	if (!trimmed)
		return (NULL);
	return (trimmed);
}

char	*get_redir_name(char *offset, int size)
{
	char	*file;

	file = ft_calloc(size, sizeof(char));
	if (!file)
		return (NULL);
	ft_strlcpy(file, offset, size);
	if (file[0] == '\'' || file[0] == '\"')
		return (trim_file_quotes(file, file[0]));
	return (file);
}