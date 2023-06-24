NAME = minitalk
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I $(LIBFT_PATH)
LDFLAGS = -L $(LIBFT_PATH)
SERVER_SRC = server.c
CLIENT_SRC = client.c
LIBFT = ft
LIBFT_PATH = libft

all: $(NAME)

$(NAME):
	make -C $(LIBFT_PATH)
	make server
	make client

server:
	$(CC) $(CFLAGS) $(SERVER_SRC) $(INCLUDE) $(LDFLAGS) -o $@

client:
	$(CC) $(CFLAGS) $(CLIENT_SRC) $(INCLUDE) $(LDFLAGS) -o $@

clean:
	make -C $(LIBFT_PATH) clean
	$(RM) $(OBJS) $(B_SRCS:.c=.o)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: bonus clean fclean re all