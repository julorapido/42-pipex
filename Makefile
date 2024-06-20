NAME = pipex
SRCS_ = pipex.c utils.c
SRCS_OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

PRINTF_DIR = ./Printf/
PRINTF = $(PRINTF_DIR)libftprintf.a

LIBFT_DIR = ./Libft/
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I./includes -I$(LIBFT_DIR) -I$(PRINTF_DIR)

all: $(LIBFT) $(NAME)

$(NAME) : $(SRCS_OBJ)
	gcc $(CFLAGS) $(SRCS_) $(INCLUDES) -o $(NAME) $(LIBFT)

$(LIBFT):
	@echo "Making Libft.."
	@make -C $(LIBFT_DIR)

$(PRINTF):
	@echo "Making Printf.."
	@make -C $(PRINTF_DIR)

clean:
	@echo "Removing .o files"
	rm -f $(SRCS_OBJ)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean all
