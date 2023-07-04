/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:58:13 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/07/04 17:45:15 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_builtin(t_data **shell, t_cmd cmd)
{
	static int	(*f[8])(t_data **, char **) = (int (*[8])(t_data **, char **))
	{NULL, &echo, &cd, &pwd, &export_bin, &unset, &env, &exit_bin};

	if (!cmd.builtin)
		return (1);
	return (f[cmd.builtin](shell, cmd.args));
}
