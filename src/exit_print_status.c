#include "minishell.h"

void	print_exit_error(int status)
{
	ft_putstr_fd("Minishell: fatal error: ", 2);
	if (status == -1)
		ft_putendl_fd("error on malloc", 2);
	else if (status == -2)
		ft_putendl_fd("signal handler error", 2);
	else if (status == -3)
		ft_putendl_fd("file open error", 2);
	else if (status == -4)
		ft_putendl_fd("file close error", 2);
	else if (status == -5)
		ft_putendl_fd("pipe open error", 2);
	else if (status == -6)
		ft_putendl_fd("pipe close error", 2);
	else if (status == -7)
		ft_putendl_fd("exec error", 2);
	else if (status == -8)
		ft_putendl_fd("fork error", 2);
	else if (status == -9)
		ft_putendl_fd("dup error", 2);
	else if (status == -10)
		ft_putendl_fd("waitpid error", 2);
}