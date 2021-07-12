.PHONY: clean all re fclean
SRCS =	./dlist_methods1.c ./dlist_methods2.c ./dlist_methods3.c ./dlist_methods4.c ./dlist.c ./stack_methods1.c
SOURCES = dlist_methods1.c dlist_methods2.c dlist_methods3.c dlist_methods4.c dlist.c stack_methods1.c
OBJS = $(SOURCES:.c=.o)
CFLAGS = -Wall -Wextra -Werror
NAME	= DLIST.a
CC	 = gcc
all:$(NAME)
$(NAME):
	@echo "\033[1;32mcompiling dlist static library"
	@gcc $(CFLAGS) -c $(SRCS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
clean:
	@echo "\033[0;33mclean DLIST obj files"
	@rm -f $(OBJS)
	@rm -f $(OBBS)
fclean: clean
	@echo "clean everything related to dlist library"
	@rm -f $(NAME)
re: fclean all