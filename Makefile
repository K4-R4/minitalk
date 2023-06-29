NAME = minitalk
CFLAGS = -Wall -Wextra -Werror
<<<<<<< HEAD
INCLUDE = -I $(LIBFT_DIR)/include
LDFLAGS = -L $(LIBFT_DIR) -l ft
SERVER = server
CLIENT = client
=======
INCLUDE = -I $(LIBFT_PATH)
LDFLAGS = -L $(LIBFT_PATH) -l $(LIBFT)
>>>>>>> 2f270b3c8c55fee64af615d4d66cd9e2b061036e
SERVER_SRC = server.c
CLIENT_SRC = client.c
LIBFT_DIR = ./libft
LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(SERVER) $(CLIENT)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(SERVER):
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) $(SERVER_SRC) -o $@

$(CLIENT):
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) $(CLIENT_SRC) -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	$(RM) server client

re: fclean all

.PHONY: bonus clean fclean re all
