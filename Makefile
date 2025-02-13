CC = cc
CFLAGS = -Wall -Wextra -Werror -I.
NAME = pipex
SRCS_DIR = ./src
SRCS =	$(SRCS_DIR)/main.c $(SRCS_DIR)/parent.c $(SRCS_DIR)/child.c \
		$(SRCS_DIR)/cmd.c $(SRCS_DIR)/utils.c $(SRCS_DIR)/pipex.c
OBJS = $(SRCS:.c=.o)
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
GREEN = \033[32m
YELLOW = \033[33m
NC = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "$(GREEN)Compiled Successfully 😎$(NC)"

$(LIBFT):
	@echo "$(YELLOW)🚧Compiling🚧$(NC)"
	@$(MAKE) -C $(LIBFT_DIR)

debug:$(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME) -g

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re