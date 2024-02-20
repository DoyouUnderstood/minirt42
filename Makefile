# Nom du programme
NAME = miniRT

# Compilateur
CC = gcc

# Flags de compilation
CFLAGS = -Wall -Wextra -Werror -I./mlx

# Chemins d'inclusion pour les librairies internes
LIBFT_DIR = lib/libft
GNL_DIR = lib/GNL
FT_PRINTF_DIR = lib/ft_printf

# Chemin vers MinilibX
MLX_DIR = lib/mlx/mlx

# Inclure le dossier pour les fichiers d'en-tête MinilibX
# Assurez-vous de remplacer `chemin_vers_minilibx` par le chemin réel vers MinilibX sur votre système
INCLUDES = -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(FT_PRINTF_DIR) -I$(MLX_DIR)

# Librairies à lier (y compris MinilibX et les librairies nécessaires pour X11 et potentiellement libbsd)
LIBS = -L$(LIBFT_DIR) -lft -L$(GNL_DIR) -lgnl -L$(FT_PRINTF_DIR) -lftprintf \
       -L$(MLX_DIR) -lmlx -L/lib/mlx/mlx -lXext -lX11 -lm

# Ajoutez `-lbsd` ici si vous êtes sur un système qui le requiert, comme Linux
# Par exemple: LIBS += -lbsd

# Fichiers source
SRCS = parser/minirt.c parser/print.c parser/parse_utils.c parser/parse.c parser/utils.c parser/free.c parser/object.c mlx/mlx.c mlx/event.c vecteur/vecteur.c vecteur/projectile.c

# Objets
OBJS = $(SRCS:.c=.o)

# Compiler les bibliothèques et le programme
$(NAME): libft gnl ft_printf $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS) $(INCLUDES)

# Compiler les bibliothèques
libft:
	make -C $(LIBFT_DIR)

gnl:
	make -C $(GNL_DIR)

ft_printf:
	make -C $(FT_PRINTF_DIR)

# Nettoyage des fichiers compilés
clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean
	make -C $(GNL_DIR) clean
	make -C $(FT_PRINTF_DIR) clean

# Nettoyage complet, y compris les bibliothèques
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(GNL_DIR) fclean
	make -C $(FT_PRINTF_DIR) fclean

# Règle pour refaire tout
re: fclean all

# Empêcher les conflits de nom
.PHONY: all clean fclean re libft gnl ft_printf
