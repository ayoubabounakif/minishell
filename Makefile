SRCS = 420sh.c \
\
./parser/mask.c \
./parser/pipelines.c \
./parser/redirection_splitting/*.c \
./parser/command_table/*.c \
./parser/command_table_generator.c \
./parser/quotes_proccessing.c\
./builtins/builtins.c \
./builtins/utils.c \
\
./builtins/__cd__.c \
./builtins/__pwd__.c \
./builtins/__echo__.c \
./builtins/__export__.c \
./builtins/__unset__.c \
./builtins/__env__.c \
./builtins/__exit__.c \
\
./environment/env.c \
\
./signals/handle_sigint.c ./signals/handle_sigquit.c ./signals/sig_handler.c \
\
get_next_line/get_next_line.c \
get_next_line/get_next_line_utils.c \

LIBRARIES = ./CPCA/CPCA.a ./libft/libft.a ./dlist/*.c

NAME = minishell
CC = gcc
CFLAGS = -ltermcap

all:$(NAME)
$(NAME):
	@$(MAKE) -C CPCA
	@$(MAKE) -C libft 
	@echo "\033[0;32mCompiling minishell"
	@gcc -g $(CFLAGS) $(LIBRARIES) $(SRCS) -D BUFFER_SIZE=1024 -o $(NAME) 

clean:
	@$(MAKE) -C CPCA clean
fclean:
	@rm -f $(NAME)
	@$(MAKE) -C CPCA fclean
	@$(MAKE) -C libft fclean
	@echo "\033[0;33mEverything cleaned"

re : fclean all