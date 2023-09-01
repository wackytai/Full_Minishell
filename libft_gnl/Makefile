# 1st makefile
NAME = libft.a

# Mandatory .c Files
C_SOURCES = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
			ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
			ft_memset.c ft_strchr.c ft_striteri.c ft_strlcat.c ft_strlcpy.c ft_strmapi.c \
			ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_tolower.c ft_toupper.c \
			ft_split.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_strncmp.c \
			ft_strlen.c ft_strjoin.c ft_substr.c ft_putnbr_fd.c ft_strdup.c \
			ft_calloc.c get_next_line_bonus.c get_next_line_utils_bonus.c \
			ft_printf.c ft_putchar.c ft_putnbr_base.c ft_putptr_base.c ft_putstr.c \
			ft_isspace.c ft_strcmp.c

# Object Files
OBJ = $(C_SOURCES:.c=.o)

#Command to Create:
CREATE = @ar -rc

#Command to Remove:
REMOVE = @rm -f

# Flags for the Compiler
CFLAGS = -Wall -Wextra -Werror

CC = @cc

#Compilation and Linking
all: $(NAME)

$(NAME):	$(OBJ)
			$(CREATE) $(NAME) $(OBJ)

bonus:	all

clean:	
		$(REMOVE) *.o

fclean:	clean
		$(REMOVE) $(NAME)

re:		clean all

.PHONY: all clean fclean re