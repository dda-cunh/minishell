/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 21:04:30 by fmouronh          #+#    #+#             */
/*   Updated: 2023/07/15 17:37:06 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	unmask_quoted_spaces(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		unset_mask(args[i], ' ');
		i++;
	}
}

static void	mask_quoted_spaces(char *trim)
{
	int	i;

	i = 0;
	while (trim[i])
	{
		if (trim[i] != '\'' && trim[i] != '\"')
			i++;
		else
			i += set_mask(&trim[i], trim[i], ' ');
	}
}

static bool	assign_tokens(char *tokens, t_cmd *cmd, char **envi)
{
	char	*trim;

	trim = ft_strdup(tokens);
	if (!trim)
		return (false);
	trim = manage_redirects(cmd, trim);
	if (!trim)
		return (false);
	mask_quoted_spaces(trim);
	cmd->args = ft_split(trim, ' ');
	free(trim);
	if (!cmd->args)
		return (false);
	unmask_quoted_spaces(cmd->args);
	cmd->builtin = is_builtin(cmd->args[0]);
	cmd->bin = get_bin(cmd->args[0], envi);
	return (true);
}

static t_cmd	*assign_next(t_data **shell, char *tokens, t_cmd *cmd_head)
{
	t_cmd	*cmd;

	cmd = NULL;
	if (tokens)
	{
		cmd = malloc(sizeof(t_cmd));
		if (!cmd)
		{
			(*shell)->cmd = cmd_head;
			exit_(-1, (*shell));
		}
	}
	return (cmd);
}

t_cmd	*parse_tokens(t_data **shell, char **tokens)
{
	t_cmd	*cmd_head;
	t_cmd	*cmd;
	int		i;

	cmd_head = malloc(sizeof(t_cmd));
	if (!cmd_head)
		exit_(-1, *shell);
	cmd = cmd_head;
	i = 0;
	while (tokens[i])
	{
		cmd->bin = NULL;
		cmd->redir = NULL;
		if (!assign_tokens(tokens[i], cmd, (*shell)->env))
		{
			free_2d(tokens);
			(*shell)->cmd = cmd_head;
			exit_(-1, (*shell));
		}
		trim_quotes(*shell, cmd->args);
		i++;
		cmd->next = assign_next(shell, tokens[i], cmd_head);
		cmd = cmd->next;
	}
	return (cmd_head);
}
