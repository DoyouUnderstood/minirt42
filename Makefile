# Nom du programme
NAME = miniRT

# Compilateur
CC = gcc

# Flags de compilation
CFLAGS = -Wall -Wextra -Werror

# Chemins d'inclusion
LIBFT_DIR = lib/libft
GNL_DIR = lib/GNL
FT_PRINTF_DIR = lib/ft_printf

# Flags d'inclusion
INCLUDES = -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(FT_PRINTF_DIR)

# Librairies à lier
LIBS = -L$(LIBFT_DIR) -lft -L$(GNL_DIR) -lgnl -L$(FT_PRINTF_DIR) -lftprintf -lm

# Fichiers source
SRCS = minirt.c ft_str_to_double.c print.c parse_utils.c parse.c main.c free.c

# Commande de compilation
$(NAME):
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -o $(NAME) $(LIBS)

# Compiler les bibliothèques
libft:
	make -C $(LIBFT_DIR)

gnl:
	make -C $(GNL_DIR)

ft_printf:
	make -C $(FT_PRINTF_DIR)

# Dépendances pour compiler les bibliothèques avant le programme principal

all: libft gnl ft_printf $(NAME)

# Nettoyage des fichiers compilés

clean:
	rm -f $(NAME)
	make -C $(LIBFT_DIR) clean
	make -C $(GNL_DIR) clean
	make -C $(FT_PRINTF_DIR) clean

# Nettoyage complet, y compris les bibliothèques

fclean: clean
	make -C $(LIBFT_DIR) fclean
	make -C $(GNL_DIR) fclean
	make -C $(FT_PRINTF_DIR) fclean

# Règle pour refaire tout
re: fclean all

# Empêcher les conflits de nom
.PHONY: all clean fclean re libft gnl ft_printf
