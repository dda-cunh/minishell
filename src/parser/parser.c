/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 21:04:30 by fmouronh          #+#    #+#             */
/*   Updated: 2023/08/11 21:30:08 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*		DEBUG		*/
// static void	print_redir_struct(t_redir *redir)
// {
// 	while (redir)
// 	{
// 		printf("cmd->redir->name = %s\n", redir->name);
// 		printf("direction: %c\n", redir->direction);
// 		printf("is double token: %d\n", redir->dbl_tkn);
// 		redir = redir->next;
// 	}
// }

// static void	print_args(char **args)
// {
// 	int	i;

// 	i = 0;
// 	while (args[i])
// 	{
// 		printf("cmd->args[%d] = %s\n", i, args[i]);
// 		i++;
// 	}
// 	printf("\n");
// }

// static void	show_cmds(t_cmd *cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd)
// 	{
// 		printf("cmd nr %d\n", i);
// 		printf("builtin nr: %d\n", cmd->builtin);
// 		if (cmd->bin)
// 			printf("cmd->bin = %s\n", cmd->bin);
// 		if (cmd->args)
// 			print_args(cmd->args);
// 		if (cmd->redir)
// 			print_redir_struct(cmd->redir);
// 		cmd = cmd->next;
// 	}
// }
/*		DEBUG		*/

/*
	parse in the following order:
		input redirects
		output redirects
		split into cmd->args
		check args[0] against builtins
		if not builtin: check with access() & assign to cmd->bin if found
*/

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

	cmd->bin = NULL;
	cmd->redir = NULL;
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
	cmd->id = -69;
	remove_quotes(cmd);
	return (true);
}

static t_cmd	*assign_next(t_data **shell, char *tokens, t_cmd *cmd_head)
{
	t_cmd	*cmd;

	cmd = NULL;
	if (tokens)
	{
		cmd = ft_calloc(1, sizeof(t_cmd));
		if (!cmd)
		{
			(*shell)->cmd = cmd_head;
			exit_(-1, (*shell));
		}
	}
	return (cmd);
}

void	parse_tokens(t_data **shell, char **tokens)
{
	t_cmd	*prev;
	t_cmd	*cmd;
	int		i;

	(*shell)->cmd = malloc(sizeof(t_cmd));
	if (!(*shell)->cmd)
		exit_(-1, *shell);
	cmd = (*shell)->cmd;
	i = 0;
	prev = NULL;
	while (tokens[i])
	{
		cmd->prev = prev;
		if (!assign_tokens(tokens[i], cmd, (*shell)->env))
		{
			free_2d(tokens);
			(*shell)->cmd = (*shell)->cmd;
			exit_(-1, (*shell));
		}
		i++;
		prev = cmd;
		cmd->next = assign_next(shell, tokens[i], (*shell)->cmd);
		cmd = cmd->next;
	}
}
