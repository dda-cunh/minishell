#include "minishell.h"

static char	*search_in_path(char *bin, char **path)
{

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

	path = get_path(char *env);
	if (path)
	{
		result = search_in_path(bin, path);
		free_2d(path);
		return (result);
	}
	return (NULL);
}
