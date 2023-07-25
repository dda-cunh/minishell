/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 21:04:30 by fmouronh          #+#    #+#             */
/*   Updated: 2023/07/25 02:00:45 by dda-cunh         ###   ########.fr       */
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
static bool	assign_tokens(char *tokens, t_cmd *cmd, char **envi)
{
	char	*trim;

	trim = ft_strdup(tokens);
	if (!trim)
		return (false);
	trim = manage_redirects(cmd, trim);
	if (!trim)
		return (false);
	cmd->args = ft_split(trim, ' ');
	free(trim);
	if (!cmd->args)
		return (false);
	cmd->builtin = is_builtin(cmd->args[0]);
	cmd->bin = get_bin(cmd->args[0], envi);
	cmd->read_tmp = 0;
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
		i++;
		cmd->next = assign_next(shell, tokens[i], cmd_head);
		cmd = cmd->next;
	}
	return (cmd_head);
}
