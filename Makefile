NAME = pipex
BONUS = pipex_bonus
SRCS = pipex.c pipex_utilis_0.c pipex_utilis_1.c
SRCSB = pipex_bonus.c pipex_bonus_utilis_0.c pipex_bonus_utilis_1.c
LIBFT = ./libft/libft.a
CFLAGS = -Wall -Werror -Wextra

all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "[+] libft ..."
	@make -C ./libft -s 

$(NAME): $(LIBFT)
	@echo "[+] pipex ..."
	@gcc $(SRCS) $(CFLAGS) $(LIBFT) -o $(NAME)

bonus: $(LIBFT) $(BONUS)

$(BONUS): $(LIBFT)
	@echo "[+] pipex_bonus ..."
	@gcc $(SRCSB) $(CFLAGS) $(LIBFT) -o $(BONUS)

clean:
	@echo "[-] clean ..."
	@make clean -C ./libft -s

fclean:
	@echo "[-] clean all ..."
	@make fclean -C ./libft -s
	@rm -f $(NAME) $(BONUS)

re:fclean all


