/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 14:49:51 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/08 17:48:49 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*prompt(t_data *shell)
{
	if (!shell->status)
		return (readline(ANSI_GREEN EXIT_OK ANSI_CYAN PROMPT ANSI_RESET));
	else
		return (readline(ANSI_RED EXIT_KO ANSI_CYAN PROMPT ANSI_RESET));
}

static void	print_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		printf("%s\n", tokens[i]);
		i++;
	}
}

int	minishell(t_data *shell)
{
	char	**tokens;
	char	*line;

	while (shell->status >= 0)
	{
		line = prompt(shell);
		if (!line)
		{
			printf("exit\n");
			return (0);
		}
		if (*line)
			add_history(line);
		tokens = lex_line(shell, line);
		free(line);
		if (!tokens)
			continue ;
		print_tokens(tokens);
		//expander(shell, tokens);
		//	parse tokens with parser
		//parse_tokens(shell, tokens);
		free_2d(tokens);
		//	send to pipeline
		//shell->status = pipex(shell);
	}
	return (shell->status);
}
