#ifndef MINSHELL_H
# define MINSHELL_H

/*
	includes go here
*/

typedef struct s_data
{
	char			**env;
	struct s_cmd	*cmd;
	int				infile;
	int				outfile;
}				t_data;

typedef struct s_cmd
{
	/*
		tokens, etc
	*/
	struct s_cmd	*next;
}				t_cmd;

#endif
