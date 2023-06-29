NAME = minitalk
CFLAGS = -Wall -Wextra -Werror
SERVER = server
CLIENT = client
INCLUDE = -I $(LIBFT_DIR)
LDFLAGS = -L $(LIBFT_DIR) -l $(LIBFT)
SERVER_SRC = server.c
SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_SRC = client.c
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
LIBFT_DIR = libft
LIBFT = ft

all: $(NAME)

$(NAME):
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) $(SERVER)
	$(MAKE) $(CLIENT)

$(SERVER): $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) $(SERVER_OBJ) -o $@

$(CLIENT): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) $(CLIENT_OBJ) -o $@

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(SERVER_OBJ) $(CLIENT_OBJ)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all

.PHONY: bonus clean fclean re all
