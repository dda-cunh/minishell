.SILENT:
NAME		= 	minishell

CC 			= 	cc

CFLAGS		= 	-Wall -Wextra -Werror -g #fsanitize=address

RM 			= 	rm -rf

INC_DIR		=	inc/

SRC_DIR		=	src/

OBJ_DIR		=	temp/

BIN_DIR		=	builtins/

PIP_DIR		=	pipex/

FT_DIR		=	libft/

FT_FULL		=	$(addprefix $(INC_DIR), $(FT_DIR))

LINKS		=	-L$(FT_FULL) -lft -lreadline

SRC			=	$(addprefix $(SRC_DIR),	minishell.c \
										utils.c \
										main.c \
										$(addprefix $(BIN_DIR), echo.c \
																cd.c \
																pwd.c \
																export.c \
																unset.c \
																env.c \
																exit.c) \
										$(addprefix $(PIP_DIR), pipex.c \
																pipex_io.c \
																pipex_get_cmd.c))

OBJ_DIRS	=	$(OBJ_DIR) $(addprefix $(OBJ_DIR), $(BIN_DIR)) $(addprefix $(OBJ_DIR), $(PIP_DIR))

OBJ 		= 	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

GREEN		= 	\033[0;32m

RESET		=	\033[0m

SUS			=	\U00000D9E

HAMMER		=	\U0001F528

BROOM		=	\U0001F9F9

$(NAME):		$(OBJ)
				printf '$(HAMMER)\n\t$(GREEN)Compiling $(NAME)$(RESET)\n'
				$(CC) $(CFLAGS) $^ -o $@ -I $(INC_DIR) $(LINKS)
				make done

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c | $(OBJ_DIRS)
				printf '$(HAMMER)\n\t$(GREEN)Compiling $(notdir $<)$(RESET)\n'
				make -C $(FT_FULL)
				$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR) -I $(FT_FULL)

$(OBJ_DIRS):
				mkdir -p $@

all: 			$(NAME)

clean:
				make clean -C $(FT_FULL)
				$(RM) $(OBJ_DIR)

fclean:			clean
				printf '$(BROOM)\n$(BROOM)\t$(GREEN)Cleaning project$(RESET)\n'
				make fclean -C $(FT_FULL)
				$(RM) $(NAME)
				printf '$(BROOM)\t\t\t$(SUS)\n'

re:				fclean all

done:
				sleep 1
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

.PHONY: 		all clean fclean re
