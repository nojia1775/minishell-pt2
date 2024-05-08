CC = cc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

OBJS_DIR = obj

SRCS = minishell.c\
		utils/utilsv1.c\
		execute/env/setup_lobby.c\
		execute/cmd/cd.c\
		execute/env/env.c\
		utils/utilsv2.c\
		execute/env/export.c\
		execute/env/unset.c\
		utils/utilsv3.c\
		execute/cmd/echo.c\
		execute/cmd/exe_cmd.c\
		utils/utilsv4.c\
		execute/cmd/pwd.c\
		execute/cmd/exit.c\
		execute/env/export2.c\
		execute/env/env2.c\
		execute/cmd/cd2.c\
		execute/env/setup_lobby2.c\
		execute/cmd/pipes2.c\
		execute/cmd/pipes3.c\
		utils/utilsv5.c\
		parsing/parsing.c \
       	parsing/quotes.c \
       	parsing/nbr_quotes.c \
       	parsing/interpretation.c \
		parsing/utilsv6.c \

OBJS = $(SRCS:.c=.o)

NAME = minishell

$(NAME): $(OBJS)
	@make -C libft42/
	@make -C ft_printf/
	$(CC) $(CFLAGS) $^ -o $@ libft42/libft.a ft_printf/libftprintf.a -lreadline

$(OBJS_DIR)/%.o: src/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

all: $(NAME)

clean:
	@make fclean -C libft42/
	@make fclean -C ft_printf/
	rm -f $(OBJS)

fclean: clean
	@make fclean -C libft42/
	@make fclean -C ft_printf/
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re