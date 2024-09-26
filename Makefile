CC = cc

CFLAGS = -Wall -Wextra -Werror -g

OBJS_DIR = obj

SRCS = minishell.c\
	execute/cmd/cd.c \
	execute/cmd/cd2.c\
	execute/cmd/check_redirection.c \
	execute/cmd/echo.c\
	execute/cmd/exec_builtin.c  \
	execute/cmd/exe_cmd.c\
	execute/cmd/exit.c\
	execute/cmd/here_doc.c\
	execute/cmd/pipes.c\
	execute/cmd/pipes2.c\
	execute/cmd/pipes3.c\
	execute/cmd/pwd.c\
	execute/env/setup_lobby.c\
	execute/env/env.c\
	execute/env/export.c\
	execute/env/unset.c\
	execute/env/export2.c\
	execute/env/env2.c\
	execute/env/setup_lobby2.c\
       	parsing/nbr_quotes.c\
	parsing/builtins/pars_export.c\
	parsing/builtins/pars_unset.c\
	parsing/files_and_redir.c \
	parsing/parsing_pt2.c \
        parsing/token_pt2.c \
        parsing/interpretation_pt2.c \
        parsing/type_token.c \
        parsing/quote_pt2.c \
	parsing/pipe.c \
	parsing/cmd_pipex.c \
	signals.c \
	utils/free.c \
	utils/utilsv1.c \
	utils/utilsv2.c \
	utils/utilsv3.c \
	utils/utilsv4.c \
	utils/utilsv5.c \
	utils/utilsv6.c \
	utils/utilsv7.c \
	utils/utilsv8.c \
	utils/utilsv9.c \
	utils/utilsv10.c \
	utils/utilsv11.c \
	utils/utilsv12.c \
	utils/utilsv13.c

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

NAME = minishell

$(NAME): $(OBJS)
	@make bonus -C libft42/
	$(CC) $(CFLAGS) $^ -o $@ libft42/libft.a -lreadline
	
$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

all: $(NAME)

clean:
	@make clean -C libft42/
	rm -rf $(OBJS_DIR)

fclean: clean
	@make fclean -C libft42/
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
