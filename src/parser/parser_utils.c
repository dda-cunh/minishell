/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:36:22 by fmouronh          #+#    #+#             */
/*   Updated: 2023/07/15 16:04:51 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_redir	*gen_redir(t_cmd *cmd, char tkn)
{
	t_redir	*redir_lst;
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->dbl_tkn = false;
	if (tkn == '<')
		redir->direction = 'i';
	else
		redir->direction = 'o';
	redir->next = NULL;
	redir_lst = cmd->redir;
	if (redir_lst)
	{
		while (redir_lst->next)
			redir_lst = redir_lst->next;
		redir_lst->next = redir;
	}
	else
		cmd->redir = redir;
	return (redir);
}

static char	*set_redir(t_cmd *cmd, char *tkns, int index, char tkn)
{
	t_redir	*redir;
	char	*trim;
	int		i;
	int		j;

	redir = gen_redir(cmd, tkn);
	if (!redir)
		return (NULL);
	i = index;
	if (tkns[++i] == tkn)
		redir->dbl_tkn = true;
	while (tkns[i] && (tkns[i] == ' ' || tkns[i] == tkn))
		i++;
	j = i;
	while (tkns[j] && tkns[j] != ' ' && tkns[j] != '<' && tkns[j] != '>')
		j++;
	redir->name = ft_calloc((j - i) + 1, sizeof(char));
	if (!redir->name)
		return (NULL);
	ft_strlcpy(redir->name, &tkns[i], (j - i) + 1);
	trim = ft_strreplace(tkns, index, (j - index + 1), " ");
	if (!trim)
		return (NULL);
	free(tkns);
	return (trim);
}

static int	skip_quoted(char *str, char tkn)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != tkn)
		i++;
	return (i);
}

char	*manage_redirects(t_cmd *cmd, char *tkns)
{
	char	*trim;
	int		i;

	trim = ft_strdup(tkns);
	if (!trim)
		return (NULL);
	i = 0;
	while (trim[i])
	{
		if (trim[i] == '\'' || trim[i] == '\"')
			i += skip_quoted(&trim[i], trim[i]);
		if (trim[i] == '<' || trim[i] == '>')
		{
			trim = set_redir(cmd, trim, i, trim[i]);
			if (!trim)
			{
				free(tkns);
				return (NULL);
			}
			i = 0;
		}
		else
			i++;
	}
	free(tkns);
	return (trim);
}