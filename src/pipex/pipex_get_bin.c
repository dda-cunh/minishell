#include "minishell.h"

static char	*search_in_path(char *bin, char **path)
{
	int		i;
	char	*tmp_path;
	char	*tmp_cmd;

	i = 0;
	while (path[i])
	{
		tmp_path = ft_strjoin(path[i++], "/");
		if (!tmp_path)
			exit_(-1, get_shell());
		tmp_cmd = ft_strjoin(tmp_path, bin);
		free(tmp_path);
		if (!tmp_cmd)
			exit_(-1, get_shell());
		if (access(tmp_cmd, F_OK) == 0)
		{
			return (tmp_cmd);
		}
		free(tmp_cmd);
	}
	print_file_error(bin, FILE_NOT_FOUND);
	return (NULL);
}

static char	**get_path(char **envp)
{
	char	**path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
		i++;
	}
	if (!envp[i])
		return (NULL);
	path = ft_split(envp[i] + 5, ':');
	if (!path)
		exit_(-1, get_shell());
	return (path);
}

char	*get_cmd_bin(char **env, char *bin)
{
	char	**path;
	char	*result;

	path = get_path(env);
	if (path)
	{
		result = search_in_path(bin, path);
		free_2d(path);
		if (access(result, X_OK) == -1 || access(result, R_OK) == -1)
		{
			print_file_error(result, FILE_NO_PERM);
			free(result);
			return (NULL);
		}
		return (result);
	}
	return (NULL);
}
