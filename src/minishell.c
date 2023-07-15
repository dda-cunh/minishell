/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 14:49:51 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/12 18:37:17 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*prompt(t_data *shell)
{
	unlink(shell->tmp_path);
	if (!shell->status)
		return (readline(ANSI_GREEN EXIT_OK ANSI_CYAN PROMPT ANSI_RESET));
	else
		return (readline(ANSI_RED EXIT_KO ANSI_CYAN PROMPT ANSI_RESET));
}

// static void	print_tokens(char **tokens)
// {
// 	int	i;

// 	i = 0;
// 	while (tokens[i])
// 	{
// 		printf("%s\n", tokens[i]);
// 		i++;
// 	}
// }

int	minishell(t_data *shell)
{
	char	**tokens;
	char	*line;

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
		tokens = lex_line(shell, line);
		free(line);
		if (!tokens)
			continue ;
		expander(shell, tokens);
		shell->cmd = parse_tokens(shell, tokens);
		free_2d(tokens);
		if (!shell->cmd)
			continue ;
		shell->status = pipex(&shell);
		shell->cmd = free_cmd(shell->cmd);
        if (errno && shell->status == errno)
			put_strerror();
	}
	return (shell->status);
}
