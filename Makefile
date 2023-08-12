.SILENT:
NAME		= 	minishell

CC 			= 	cc

CFLAGS		= 	-Wall -Wextra -Werror -g

RM 			= 	rm -rf

VAL_SUPPRE	=	readline.supp

DEBUG_DIR	= 	debug/

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
																parser_utils_patch.c \
																parser.c) \
										$(addprefix $(PIP_DIR), pipex_utils.c \
																pipex_io.c \
																pipex_io_patch.c \
																pipeline.c \
																pipex.c))

OBJ_DIRS	=	$(OBJ_DIR)	$(addprefix $(OBJ_DIR), $(BIN_DIR)) \
							$(addprefix $(OBJ_DIR), $(LEX_DIR)) \
							$(addprefix $(OBJ_DIR), $(PAR_DIR)) \
							$(addprefix $(OBJ_DIR), $(PIP_DIR))

OBJ 		= 	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

GREEN		= 	\033[0;32m

RED			=	\033[0;31m

RESET		=	\033[0m

SUS			=	\U00000D9E

HAMMER		=	\U0001F528

BROOM		=	\U0001F9F9

$(NAME):		$(OBJ) | $(SRC)
				printf '$(HAMMER)\t$(GREEN)Compiling $(NAME)$(RESET)\n'
				$(CC) $(CFLAGS) $^ -o $@ -I $(INC_DIR) $(LINKS)
				make compiled

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c | $(OBJ_DIRS)
				make -C $(LFT_FULL)
				printf '$(HAMMER)\t'
				printf "$(GREEN)Compiling $(NAME) objects... $(RED)%-33.33s\r" $(notdir $@)
				$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

$(OBJ_DIRS):
				mkdir -p $@

all: 			$(NAME)

clean:
				make fclean -C $(LFT_FULL)
				if [ -d $(OBJ_DIR) ]; then $(RM) $(OBJ_DIR); fi
				if [ -d $(DEBUG_DIR) ]; then $(RM) $(DEBUG_DIR); fi

fclean:			clean
				printf '$(BROOM)\n$(BROOM)\t$(GREEN)Cleaning project$(RESET)\n'
				$(RM) $(NAME)
				printf '$(BROOM)\t\t\t$(SUS)\n'

re:				fclean all

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

valgrind:		$(NAME) | $(DEBUG_DIR)
				if ! [ -f $(VAL_SUPPRE) ]; then printf "{\n\tignore_libreadline_conditional_jump_errors\n\tMemcheck:Leak\n\t...\n\tobj:*/libreadline.so.*\n}" > $(addprefix $(DEBUG_DIR), $(VAL_SUPPRE)); fi
				valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --suppressions=$(addprefix $(DEBUG_DIR), $(VAL_SUPPRE)) --track-origins=yes --log-file=$(addprefix $(DEBUG_DIR), "valgrind.txt") ./minishell

$(DEBUG_DIR):
				mkdir -p $@

run:			all
				./minishell

.PHONY: 		all clean fclean re
