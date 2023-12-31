/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:36:22 by fmouronh          #+#    #+#             */
/*   Updated: 2023/08/11 17:22:53 by dda-cunh         ###   ########.fr       */
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

static int	skip_quoted(char *str, char tkn)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != tkn)
		i++;
	return (i);
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
	j = praise_teh_norminette(tkns, i);
	redir->name = get_redir_name(&tkns[i], (j - i) + 1);
	trim = ft_strreplace(tkns, index, (j - index), " ");
	free(tkns);
	if (!redir->name || !trim)
		return (NULL);
	return (trim);
}

char	*manage_redirects(t_cmd *cmd, char *tkns)
{
	char	*trim;
	int		i;

	trim = ft_strdup(tkns);
	if (!trim)
		return (NULL);
	i = -1;
	while (trim[++i])
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
			i = -1;
		}
	}
	free(tkns);
	return (trim);
}
