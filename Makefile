# Nom du programme
NAME = miniRT

# Compilateur
CC = gcc

# Flags de compilation
CFLAGS = -Wall -Wextra -Werror

# Fichiers source
SRCS = minirt.c ft_str_to_double.c ft_split.c print.c parse_utils.c parse.c main.c ft_strtod.c

# Commande de compilation
$(NAME):
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME) -lm

# Nettoyage des fichiers compilés
clean:
	rm -f $(NAME)

# Nettoyage complet, même si ici il fait la même chose que clean
fclean: clean

# Règle pour refaire tout
re: fclean all

# Empêcher les conflits de nom
.PHONY: all clean fclean re


