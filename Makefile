.SILENT:
NAME		= 	minishell

CC 			= 	cc

CFLAGS		= 	-Wall -Wextra -Werror -g

VAL_SUPPRE	=	readline.supp

RM 			= 	rm -rf

INC_DIR		=	inc/

SRC_DIR		=	src/

OBJ_DIR		=	temp/

BIN_DIR		=	builtins/

PIP_DIR		=	pipex/

LEX_DIR		=	lexer/

PAR_DIR		=	parser/

LFT_DIR		=	libft/

LFT_FULL	=	$(addprefix $(INC_DIR), $(LFT_DIR))

LINKS		=	-L$(LFT_FULL) -lft -lreadline

SRC			=	$(addprefix $(SRC_DIR),	exec_builtin.c \
										init_shell.c \
										init_shell_env.c \
										signals.c \
										token_masks.c \
										minishell.c \
										expander.c \
										get_bin.c \
										utils.c \
										exit_.c \
										main.c \
										$(addprefix $(BIN_DIR), export.c \
																export_noargs.c \
																unset.c \
																echo.c \
																exit.c \
																pwd.c \
																env.c \
																cd.c) \
										$(addprefix $(LEX_DIR), lex_validator_utils.c \
																lex_validator.c \
																lexer.c) \
										$(addprefix $(PAR_DIR), parser_utils.c \
																parser.c) \
										$(addprefix $(PIP_DIR), pipex_io.c \
																pipex.c))

OBJ_DIRS	=	$(OBJ_DIR)	$(addprefix $(OBJ_DIR), $(BIN_DIR)) \
							$(addprefix $(OBJ_DIR), $(LEX_DIR)) \
							$(addprefix $(OBJ_DIR), $(PAR_DIR)) \
							$(addprefix $(OBJ_DIR), $(PIP_DIR))

OBJ 		= 	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

GREEN		= 	\033[0;32m

RESET		=	\033[0m

SUS			=	\U00000D9E

HAMMER		=	\U0001F528

BROOM		=	\U0001F9F9

$(NAME):		$(OBJ) | $(SRC)
				printf '$(HAMMER)\n\t$(GREEN)Compiling $(NAME)$(RESET)\n'
				$(CC) $(CFLAGS) $^ -o $@ -I $(INC_DIR) $(LINKS)
				make done

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c | $(OBJ_DIRS)
				make -C $(LFT_FULL)
				printf '$(HAMMER)\n\t$(GREEN)Compiling $(notdir $<)$(RESET)\n'
				$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR) -I $(LFT_FULL)

$(OBJ_DIRS):
				mkdir -p $@

all: 			$(NAME)

clean:
				make clean -C $(LFT_FULL)
				$(RM) $(OBJ_DIR)
				if [ -f $(VAL_SUPPRE) ]; then rm $(VAL_SUPPRE) valgrind.txt; fi

fclean:			clean
				printf '$(BROOM)\n$(BROOM)\t$(GREEN)Cleaning project$(RESET)\n'
				make fclean -C $(LFT_FULL)
				$(RM) $(NAME)
				printf '$(BROOM)\t\t\t$(SUS)\n'

re:				fclean all

done:
				clear
				make compiled

compiled:
				printf "															 	\n"
				printf "$(GREEN)	$(NAME)							 			$(RESET)\n"
				printf "$(GREEN)                             _  _             _ $(RESET)\n"
				printf "$(GREEN)                            (_)| |           | |$(RESET)\n"
				printf "$(GREEN)  ____   ___   ____   ____   _ | |  ____   _ | |$(RESET)\n"
				printf "$(GREEN) / ___) / _ \ |    \ |  _ \ | || | / _  ) / || |$(RESET)\n"
				printf "$(GREEN)( (___ | |_| || | | || | | || || |( (/ / ( (_| |$(RESET)\n"
				printf "$(GREEN) \____) \___/ |_|_|_|| ||_/ |_||_| \____) \____|$(RESET)\n"
				printf "$(GREEN)                     |_|                        $(RESET)\n"
				printf "																\n"

valgrind:		$(NAME)
				if ! [ -f $(VAL_SUPPRE) ]; then printf "{\n\tignore_libreadline_conditional_jump_errors\n\tMemcheck:Leak\n\t...\n\tobj:*/libreadline.so.*\n}" > $(VAL_SUPPRE); fi
				valgrind --leak-check=full --show-leak-kinds=all --suppressions=$(VAL_SUPPRE) --track-origins=yes --log-file="valgrind.txt" ./minishell

run:			all
				./minishell

.PHONY: 		all clean fclean re
