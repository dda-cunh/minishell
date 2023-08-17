/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:54:33 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/08/17 11:33:39 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	changedir(t_data **shell, char *path)
{
	char	*old_pwd;
	char	*new_pwd;
	int		ret;

	old_pwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
		ret = errno;
	else
	{
		update_env_val(shell, "OLDPWD", old_pwd, true);
		new_pwd = getcwd(NULL, 0);
		update_env_val(shell, "PWD", new_pwd, true);
		free(new_pwd);
		ret = 0;
	}
	free(old_pwd);
	return (ret);
}

static int	do_alt(t_data **shell, char *alt_var)
{
	char	*alt_value;
	int		ret;

	alt_value = get_env_val(*shell, alt_var);
	if (!*alt_value)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(alt_var, 2);
		ft_putendl_fd(" not set", 2);
		ret = 1;
	}
	else
		ret = changedir(shell, alt_value);
	free(alt_value);
	return (ret);
}

int	cd(t_data **shell, char **path)
{
	int		ret;

	ret = 0;
	if (!path[0])
		ret = do_alt(shell, "HOME");
	else if ((*path)[0] == '-' && !(*path)[1])
		ret = do_alt(shell, "OLDPWD");
	else
	{
		if (*(path + 1))
		{
			put_strerror("minishell: cd: too many arguments", 0);
			return (1);
		}
		else
		{
			ret = changedir(shell, *path);
			if (ret)
			{
				ret = 1;
				put_strerror("minishell: cd: ", 1);
			}
		}
	}
	return (ret);
}
