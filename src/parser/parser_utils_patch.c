/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_patch.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:26:00 by fmouronh          #+#    #+#             */
/*   Updated: 2023/08/17 14:37:43 by dda-cunh         ###   ########.fr       */
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

static int	skip_quotes(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}

static char	*search_quotes(char *str)
{
	char	*result;
	int		start;
	int		i[2];

	result = NULL;
	start = 0;
	i[0] = 0;
	i[1] = 0;
	while (str[i[0]])
	{
		if (str[i[0]] == '\"' || str[i[0]] == '\'')
		{
			i[1] = i[0];
			i[0] += skip_quotes(&str[i[0]], str[i[0]]);
			result = do_remove(result, str, start, i);
			i[0]++;
			start = i[0];
		}
		else
			i[0]++;
	}
	if (start == 0)
		return (str);
	free(str);
	return (result);
}

void	remove_quotes(t_cmd *cmd)
{
	t_redir	*redir;
	int		i;

	redir = cmd->redir;
	i = 0;
	while (cmd->args[i])
	{
		cmd->args[i] = search_quotes(cmd->args[i]);
		i++;
	}
	while (redir)
	{
		redir->name = search_quotes(redir->name);
		redir = redir->next;
	}
}
