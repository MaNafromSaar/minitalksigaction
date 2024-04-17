CC = cc
CFLAGS = -Wall -Wextra -Werror
PATH_SRC = ./
SRCS = client.c server2.c
EXECS = $(SRCS:%.c=%)

all: $(EXECS)

%: $(PATH_SRC)%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECS)

fclean: clean
	rm -f client server2

re: fclean all

.PHONY: all clean fclean re
