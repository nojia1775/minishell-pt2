CC = cc

CFLAGS = -Wall -Wextra -Werror

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
		execute/cmd/pipes.c\
		execute/cmd/pipes2.c\
		execute/cmd/pipes3.c\
		utils/utilsv5.c\
		parsing/parsing.c\
       	parsing/quotes.c\
       	parsing/nbr_quotes.c\
       	parsing/interpretation.c\
		parsing/utilsv6.c\
		signals.c\
		execute/cmd/here_doc.c\
		parsing/builtins/pars_export.c\
		utils/utilsv7.c\
		parsing/builtins/pars_unset.c\
		parsing/parsing_pt2.c \
       parsing/token_pt2.c \
       parsing/interpretation_pt2.c \
       parsing/type_token.c \
       parsing/quote_pt2.c \
		utils/utilsv8.c \
		parsing/pipe.c \
		parsing/redir.c \
		execute/cmd/exec_builtin.c

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

NAME = minishell

$(NAME): $(OBJS)
	@make -C libft42/
	@make -C ft_printf/
	@make -C get_next_line/
	$(CC) $(CFLAGS) $^ -o $@ libft42/libft.a ft_printf/libftprintf.a get_next_line/gnl.a -lreadline
	
$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

all: $(NAME)

clean:
	@make fclean -C libft42/
	@make fclean -C get_next_line/
	@make fclean -C ft_printf/
	rm -f $(OBJS)

fclean: clean
	@make fclean -C libft42/
	@make fclean -C get_next_line/
	@make fclean -C ft_printf/
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re