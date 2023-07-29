#include "minishell.h"

void	print_file_error(char *filename, char *err)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err, 2);
}
