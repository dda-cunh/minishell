/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 14:49:51 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/04 19:40:58 by dda-cunh         ###   ########.fr       */
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

static int	new_shell(char **envi)
{
	t_data	*shell;
	int		child_pid;
	int		status;

	child_pid = fork();
	if (child_pid == -1)
		return (2);
	if (child_pid == 0)
	{
		shell = init_shell(envi);
		if (!shell)
			return (exit_(-1, NULL));
		return (exit_(minishell(shell), shell));
	}
	waitpid(child_pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	minishell(t_data *shell)
{
	char	*line;

	(void) shell;
	while (1)
	{
		line = prompt(shell);
		if (!line)
		{
			printf("\n");
			return (0);
		}
		add_history(line);
		if (!ft_strncmp(line, "minishell", 10)
			|| ! ft_strncmp(line, "./minishell", 12))
			shell->status = new_shell(shell->env);
		/*	UPDATE SHELL WITH PARSED LINE	*/
		char **args = ft_split(&line[2], ' ');
		shell->status = exec_builtin(&shell, (t_cmd){NULL, args, NULL,
				NULL, 0, 0, ft_atoi(&line[0]), NULL});
		free(args);
		free(line);
		// pipex(shell);
	}
	return (0);
}
