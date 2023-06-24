NAME = minitalk
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I $(LIBFT_DIR)/include
LDFLAGS = -L $(LIBFT_DIR) -l ft
SERVER = server
CLIENT = client
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
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all

.PHONY: bonus clean fclean re all
