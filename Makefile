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
./parser/command_table_generator2.c \
./parser/quotes_proccessing.c \
./parser/firstTokenExpander.c \
./parser/firstTokenExpander2.c \
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
./execution/executionUtils/checkExecutable.c \
./execution/executionUtils/checkDirectory.c \
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
./signals/sig_handler.c \
\

NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra #-fsanitize=address
LDFLAGS= -L /goinfre/$(USER)/.brew/opt/readline/lib
CPPFLAGS= -I /goinfre/$(USER)/.brew/opt/readline/include
READLINE = -lreadline $(LDFLAGS) $(CPPFLAGS)
LIBRARIES = ./CPCA/CPCA.a ./libft/libft.a ./dlist/DLIST.a

all: $(NAME)

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

.PHONY: clean fclean all re