NAME	= 	pipex.a

CC 		= 	cc

AR		=	ar rcs

CFLAGS	= 	-c -Wall -Wextra -Werror

RM 		= 	rm -f

SRC		= 	pipex.c \
			pipex_io.c \
			pipex_get_cmd.c

OBJ 	= 	$(SRC:%.c=%.o)

$(NAME):	$(OBJ)
			$(AR) $(NAME) $(OBJ)

$(OBJ): 	$(SRC)
			$(CC) $(CFLAGS) $(SRC)

all: 		$(NAME)

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean	all

.PHONY: 	all clean fclean re
