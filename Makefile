NAME= pipex

SRCS= pipex_path.c pipex_utils.c pipex.c
OBJS= $(SRCS:.c=.o)

RM= rm -rf
CC = cc
CFLAGS= -Wall -Werror -Wextra

LIBFT_DIR= libft
LIBFT= $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re