#include "minishell.h"

void	print_file_error(char *filename, int err)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	if (err == FILE_NOT_FOUND)
		ft_putendl_fd("No such file or directory", 2);
	else if (err == FILE_NO_PERM)
		ft_putendl_fd("Permission denied", 2);
	else if (err == CMD_NOT_FOUND)
		ft_putendl_fd("command not found", 2);
}
