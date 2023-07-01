#ifndef MINSHELL_H
# define MINSHELL_H

# include <dirent.h>
# include <signal.h>
# include "libft.h"
# include "pipex.h"

typedef struct s_data
{
	char			**env;
	struct s_cmd	*cmd;
	int				infile;
	int				outfile;
}				t_data;

typedef struct s_cmd
{
	char			*bin;
	char			*args;
	struct s_cmd	*next;
}				t_cmd;

#endif
