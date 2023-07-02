/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 14:49:51 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/02 20:46:22 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	minishell(t_data *shell)
{
	char	*line;

	(void) shell;
	shell->status = 0;
	while (1)
	{
		if (!shell->status)
			line = readline(ANSI_GREEN EXIT_OK ANSI_CYAN PROMPT ANSI_RESET);
		else
			line = readline(ANSI_RED EXIT_KO ANSI_CYAN PROMPT ANSI_RESET);
		if (!line)
		{
			printf("\n");
			return (0);
		}
		/*	UPDATE SHELL WITH PARSED LINE	*/
		char *str = get_env_val(shell, line);
		if (str)
		{
			printf("%s\n", str);
			free(str);
		}
		free(line);
		shell->status = 1;
		// pipex(shell);
	}
	return (0);
}
