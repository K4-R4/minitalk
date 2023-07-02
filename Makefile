NAME = minitalk
CFLAGS = -Wall -Wextra -Werror
SERVER = server
CLIENT = client
INCLUDE = -I $(LIBFT_DIR)
LDFLAGS = -L $(LIBFT_DIR) -l $(LIBFT)
SERVER_MSRC = server.c
CLIENT_MSRC = client.c
SERVER_BSRC = server_bonus.c
CLIENT_BSRC = client_bonus.c
LIBFT_DIR = libft
LIBFT = ft

ifdef is_bonus
	SERVER_OBJ = $(SERVER_BSRC:.c=.o)
	CLIENT_OBJ = $(CLIENT_BSRC:.c=.o)
else
	SERVER_OBJ = $(SERVER_MSRC:.c=.o)
	CLIENT_OBJ = $(CLIENT_MSRC:.c=.o)
endif

all: $(NAME)

$(NAME):
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) $(SERVER)
	$(MAKE) $(CLIENT)

$(SERVER): $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) $(SERVER_OBJ) -o $@

$(CLIENT): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) $(CLIENT_OBJ) -o $@

bonus:
	$(MAKE) is_bonus=1

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(SERVER_MSRC:.c=.o) $(SERVER_BSRC:.c=.o) $(CLIENT_MSRC:.c=.o) $(CLIENT_BSRC:.c=.o)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all

.PHONY: bonus clean fclean re all
