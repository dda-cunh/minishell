/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:23:56 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/02 16:32:59 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// static int	minishell(t_data *shell)
// {
// 	char	*line;

// 	(void) shell;
// 	shell->status = 0;
// 	while (1)
// 	{
// 		if (!shell->status)
// 			line = readline(ANSI_GREEN EXIT_OK ANSI_CYAN PROMPT ANSI_RESET);
// 		else
// 			line = readline(ANSI_RED EXIT_KO ANSI_CYAN PROMPT ANSI_RESET);
// 		if (!line)
// 		{
// 			printf("\n");
// 			return (0);
// 		}
// 		/*	UPDATE SHELL WITH PARSED LINE	*/
// 		char *str = get_env_val(shell, line);
// 		printf("%s\n", str);
// 		free(str);
// 		free(line);
// 		shell->status = 1;
// 		// pipex(shell);
// 	}
// 	return (0);
// }

int	main(int ac, char **av, char **envi)
{
	t_data	*shell;

	(void) ac;
	(void) av;
	(void) envi;
	shell = init_shell(envi);
	if (!shell)
		return (exit_(-1, NULL));
	update_env_val(shell, "USER", "NEWUSER");
	exit_(env(shell), shell);
	// return (exit_(minishell(shell), shell));
}
