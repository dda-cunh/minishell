/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:23:56 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/01 20:21:29 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	minishell(t_data *shell)
{
	char	*line;

	(void) shell;
	while (1)
	{
		line = readline(ANSI_CYAN PROMPT ANSI_RESET);
		if (!line)
		{
			printf("\n");
			return (127);
		}
		printf("%s\n", line);
		//update shell with parsed line;
		pipex(shell);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	*shell;

	(void) ac;
	(void) av;
	(void) env;
	// shell = init_shell(env);
	shell = NULL;
	return (exit_(minishell(shell), shell));
}
