/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:25:39 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/04 17:48:36 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pwd(t_data **shell, char **args)
{
	char	*pwd_val;

	(void) shell;
	(void) args;
	pwd_val = getcwd(NULL, 0);
	if (!pwd_val)
	{
		exit_(-1, *shell);
	}
	ft_putendl_fd(pwd_val, 1);
	free(pwd_val);
	return (0);
}
