.SILENT:
NAME	= 	libft.a

CC 		= 	clang

AR		=	ar rcs

SRC		= 	ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strlen.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strnstr.c \
			ft_strncmp.c \
			ft_strreplace.c \
			ft_atoi.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_striteri.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_read_write_fd.c \
			ft_free_2d.c \
			ft_close_fds.c \
			ft_len_2d.c \
			ft_notdir.c \
			ft_strdup_tail.c \
			ft_sisnum.c \
			ft_sislong.c \
			get_next_line.c \
			get_next_line_utils.c

SRCB	=	ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \

OBJ 	= 	$(SRC:%.c=%.o)

OBJB	=	$(SRCB:%.c=%.o)

CFLAGS	= 	-c -Wall -Wextra -Werror

RM 		= 	rm -f

GREEN		= 	\033[0;32m

RED			=	\033[0;31m

RESET		=	\033[0m

SUS			=	\U00000D9E

HAMMER		=	\U0001F528

BROOM		=	\U0001F9F9


$(NAME):	$(OBJ)
			$(AR) $(NAME) $(OBJ)

$(OBJ): 	$(SRC)
			printf '$(HAMMER)\t'
			printf "$(GREEN)Compiling $(RED)$(NAME)$(RESET)\n"
			$(CC) $(CFLAGS) $(SRC)

$(OBJB): 	$(SRCB)
			$(CC) $(CFLAGS) $(SRCB)
			$(AR) $(NAME) $(OBJB)

all: 		$(NAME)

bonus:		$(OBJB)

clean:	
			$(RM) $(OBJ) $(OBJB)

fclean:		clean
			$(RM) $(NAME)

re:			fclean	all

.PHONY: 	all clean fclean re