#Bugs found

## SHELL RETURN STATUS

### invalid command:
Minishell:
	`✔ minishell →  dfsfsgg`
	`dfsfsgg: command not found`
	`✘ minishell →  echo $?`
	`255`

Bash:
	`fmouronh@c2r3s5:~/Documents/projects/minishell$ sbvvwvobv`
	`sbvvwvobv: command not found`
	`fmouronh@c2r3s5:~/Documents/projects/minishell$ echo $?`
	`127`

### here-doc:
On Ctrl+C:
	`✔ minishell →  << EOF cat`
	`minihell<>> spam`
	`minihell<>> eggs`
	`minihell<>> ^C`
	`spam`
	`eggs`
	`✔ minishell →   `

On Ctrl+D:
	`✔ minishell →  << EOF cat`
	`minihell<>> spam`
	`minihell<>> eggs`
	`minihell<>> spam`
	`eggs`
	`✔ minishell →  `


### Return status:
SIGINT on piped blocking commands (ex `cat | cat | ls`) is returning wrong value
Minishell:
	`✔ minishell →  cat | cat | ls`
	`inc  Makefile  minishell  README.md  src  temp`
	`	`
	`^C`
	`✘ minishell →  echo $?`
	`130`
	`✔ minishell →  `

Bash:
	`fmouronh@c2r3s5:~/Documents/projects/minishell$ cat | cat | ls`
	`inc  Makefile  minishell  README.md  src  temp`
	`	`
	`^C`
	`fmouronh@c2r3s5:~/Documents/projects/minishell$ echo $?`
	`0`
	`fmouronh@c2r3s5:~/Documents/projects/minishell$ `

