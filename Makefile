SRCS = 420sh.c \
\
./parser/mask.c \
./parser/pipelines.c \
./parser/redirection_splitting/*.c \
./parser/command_table/*.c \
./parser/command_table_generator.c \
./parser/quotes_proccessing.c\
./parser/env_variables.c\
./parser/expand_env_vars.c\
./parser/syntax_checking.c\
\
./execution/executeParsedLine.c \
./execution/forkPipes.c \
./execution/spawnProc.c \
./execution/inputOutputRedirection.c \
./execution/executeBuiltins.c \
\
./execution/executionUtils/binPath.c \
./execution/executionUtils/dup2InputOutput.c \
./execution/executionUtils/isBuiltin.c \
./execution/executionUtils/printErrorMessage.c \
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
# \
# get_next_line/get_next_line.c \
# get_next_line/get_next_line_utils.c \

LIBRARIES = ./CPCA/CPCA.a ./libft/libft.a ./dlist/*.c

NAME = minishell
CC = gcc
CFLAGS = -ltermcap

all:$(NAME)
$(NAME):
	@$(MAKE) -C CPCA
	@$(MAKE) -C libft 
	@echo "\033[0;32mCompiling minishell"
	@gcc $(CFLAGS) $(LIBRARIES) $(SRCS) -o $(NAME) -lreadline



clean:
	@$(MAKE) -C CPCA clean
fclean:
	@rm -f $(NAME)
	@$(MAKE) -C CPCA fclean
	@$(MAKE) -C libft fclean
	@echo "\033[0;33mEverything cleaned"

re : fclean all