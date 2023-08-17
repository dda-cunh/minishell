/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 14:49:51 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/08/17 16:56:19 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
// 		printf("cmd nr %d\n", i++);
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

static char	*prompt(t_data *shell)
{
	char	*line;

	if (shell->sigint)
	{
		if (shell->status == 131)
			ft_putstr_fd("Quit (core dumped)", 2);
		ft_putendl_fd("", 2);
	}
	if (!shell->status)
		line = readline(ANSI_GREEN EXIT_OK ANSI_CYAN PROMPT ANSI_RESET);
	else
		line = readline(ANSI_RED EXIT_KO ANSI_CYAN PROMPT ANSI_RESET);
	if (!line)
	{
		ft_putendl_fd("exit\n", 2);
		exit_(shell->status, shell);
	}
	if (*line)
		add_history(line);
	return (line);
}

int	minishell(t_data *shell)
{
	char	**tokens;
	char	*line;

	while (true)
	{
		flush_stdout();
		if (signal(SIGINT, main_sig_handler) == SIG_ERR
			|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			exit_(-3, shell);
		line = prompt(shell);
		tokens = lex_line(shell, line);
		free(line);
		if (!tokens)
			continue ;
		expander(shell, tokens);
		parse_tokens(&shell, tokens);
		free_2d(tokens);
		if (!shell->cmd)
			continue ;
		shell->status = pipex(&shell, shell->cmd);
		shell->cmd = free_cmd(shell->cmd);
	}
	return (shell->status);
}
