NAME = libftprintf.a

SOURCES = ft_printf.c \
          list.c \
          xx_conversion.c \
          sc%_conversion.c \
          upid_conversion.c \
            plus.c

OBJECTS = $(SOURCES:.c=.o)


FLAGS = -Wall -Wextra -Werror

CC = cc $(FLAGS)

all: $(NAME)

clean:
		rm -f $(OBJECTS)

fclean:	clean
			rm -f $(NAME)

re:	fclean $(NAME)

$(NAME): $(SOURCES) $(OBJECTS)
	ar rc $(NAME) $(OBJECTS)

.PHONY:				all clean fclean re
