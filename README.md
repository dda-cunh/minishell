#Bugs found

### Precedence of redirect management before execution, in pipex:
Bash:\
	`fmouronh@c2r3s5:~/Documents/projects/minishell$ ls > out | << EOF cat`\
	`> ^C`\
	`fmouronh@c2r3s5:~/Documents/projects/minishell$ ls`\
	`inc  Makefile  minishell  README.md  src  temp`\
	`fmouronh@c2r3s5:~/Documents/projects/minishell$`

Minishell:\
	`✔ minishell →  ls > out | << EOF cat`\
	`minihell<>> ^C`\
	`✘ minishell →  ls`\
	`inc  Makefile  minishell  out  README.md  src  temp`


### File lookup, possibly in get_bin:	FIXED
Bash:\
	`fmouronh@c2r3s5:~/Documents/projects/minishell$ /bin/ls/filethatdoesntexist`\
	`bash: /bin/ls/filethatdoesntexist: Not a directory`\
	`fmouronh@c2r3s5:~/Documents/projects/minishell$ /nofolder/nofile`\
	`bash: /nofolder/nofile: No such file or directory`\
	`fmouronh@c2r3s5:~/Documents/projects/minishell$ /bin/ls filethatdoesntexist`\
	`/bin/ls: cannot access 'filethatdoesntexist': No such file or directory`\
	`fmouronh@c2r3s5:~/Documents/projects/minishell$ `


Minishell:\
	`✘ minishell →  /bin/ls/filethatdoesntexist`\
	`✘ minishell →  /nofolder/nofile`\
	`✘ minishell →  /bin/ls filethatdoesntexist`\
	`/bin/ls: cannot access 'filethatdoesntexist': No such file or directory`


### $PATH search needs to be done from left to right
For this test, there were two executables named `test_bin`, in paths `~/Documents/projects` and `~/Documents/projects/minishell`\
They are a Hello World and a copy of minishell, respectively

Bash:\
	`fmouronh@c2r3s5:~/Documents/projects/minishell$ export PATH=/nfs/homes/fmouronh/Documents/projects:/nfs/homes/fmouronh/Documents/projects/minishell`\
	`fmouronh@c2r3s5:~/Documents/projects/minishell$ test_bin`\
	`Hello World`\
	`fmouronh@c2r3s5:~/Documents/projects/minishell$ `

Minishell:\
	`✔ minishell →  echo $SHLVL`\
	`2`\
	`✔ minishell →  export PATH=/nfs/homes/fmouronh/Documents/projects:/nfs/homes/fmouronh/Documents/projects/minishell`\
	`✔ minishell →  ls`\
	`ls: command not found`\
	`✘ minishell →  test_bin`\
	`test_bin: command not found`\
	`✔ minishell →  echo $SHLVL`\
	`3`\
	`✔ minishell →  `

