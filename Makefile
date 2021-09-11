SRCS = 420sh.c \
\
./parser/mask_helpers.c\
./parser/mask.c \
./parser/pipelines.c \
./parser/redirection_splitting/reder_split.c \
./parser/redirection_splitting/reder_split1.c \
./parser/command_table/command_table.c \
./parser/command_table/command_table_methods.c \
./parser/command_table/command_table_methods1.c \
./parser/command_table/fill_cmd_table.c \
./parser/command_table_generator.c \
./parser/command_table_generator1.c \
./parser/quotes_proccessing.c \
./parser/env_variables.c \
./parser/env_variables2.c \
./parser/syntax_checking.c \
./parser/syntax_checking2.c \
./parser/tokens.c \
\
./heredoc/heredoc.c \
./heredoc/generate_random_value.c \
./heredoc/processHeredoc.c \
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
./environment/env_subroutines.c \
./environment/env_getters.c \
./environment/env.c \
./environment/env_expansion.c \
\
./signals/handle_sigint.c \
./signals/handle_sigquit.c \
./signals/sig_handler.c \
\

LIBRARIES = ./CPCA/CPCA.a ./libft/libft.a ./dlist/DLIST.a

NAME = minishell
CC = gcc
CFLAGS = -g3 -Wall -Wextra -Werror
LDFLAGS= -L /goinfre/$(USER)/.brew/opt/readline/lib
CPPFLAGS= -I /goinfre/$(USER)/.brew/opt/readline/include
READLINE = -lreadline $(LDFLAGS) $(CPPFLAGS)

all:$(NAME)
$(NAME):
	@$(MAKE) -C CPCA
	@$(MAKE) -C libft 
	@$(MAKE) -C dlist 
	@echo "\033[0;32mCompiling minishell"
	@$(CC) $(CFLAGS) $(SRCS) $(LIBRARIES) -o $(NAME) $(READLINE)
	@rm -rf minishell.dSYM
	@rm -rf .vscode

clean:
	@$(MAKE) -C CPCA clean

fclean:
	@rm -f $(NAME)
	@$(MAKE) -C CPCA fclean
	@$(MAKE) -C libft fclean
	@$(MAKE) -C dlist fclean
	@echo "\033[0;33mEverything cleaned"

re : fclean all