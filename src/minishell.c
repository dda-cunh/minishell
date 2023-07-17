/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 14:49:51 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/15 18:18:53 by dda-cunh         ###   ########.fr       */
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

static t_cmd	*manage_line(t_data *shell, char *line)
{
	char	**tokens;
	t_cmd	*cmd;

	tokens = lex_line(shell, line);
	free(line);
	if (!tokens)
		return (NULL);
	expander(shell, tokens);
	cmd = parse_tokens(&shell, tokens);
	free_2d(tokens);
	return (cmd);
}

static char	*prompt(t_data *shell)
{
	unlink(shell->tmp_path);
	if (!shell->status)
		return (readline(ANSI_GREEN EXIT_OK ANSI_CYAN PROMPT ANSI_RESET));
	else
		return (readline(ANSI_RED EXIT_KO ANSI_CYAN PROMPT ANSI_RESET));
}

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
/*	else if (sig == SIGQUIT)
		return ;*/
}

int	minishell(t_data *shell)
{
	char	*line;

	if (signal(SIGINT, sig_handler) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit_(-3, shell);
	while (true)
	{
		line = prompt(shell);
		if (!line)
		{
			printf("exit\n");
			exit_(0, shell);
		}
		if (*line)
			add_history(line);
		shell->cmd = manage_line(shell, line);
		if (!shell->cmd)
			continue ;
		shell->status = pipex(&shell, shell->cmd);
		shell->cmd = free_cmd(shell->cmd);
		if (errno && shell->status == errno)
			put_strerror();
	}
	return (shell->status);
}
