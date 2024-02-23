#include "../include/vecteur.h"
#include "../include/mlxinit.h"

typedef struct s_projectile {
    t_tuple position;
    t_tuple vecteur;
    t_tuple position_final;
} t_projectile;


t_mlx *init_graphics(void) 
{
    t_mlx *mlx = mlx_init_and_create_window(800, 600, "Projectile Simulation");
    if (!mlx || !mlx_create_image(mlx)) {
        mlx_cleanup(mlx);
        exit(1);
    }
    return mlx;
}


// int main() 
// {
//     t_mlx *mlx = init_graphics();
//     if (!mlx)
//         return (EXIT_FAILURE);
//     mlx_hook(mlx->win, 17, 0L, close_window, mlx);
//     mlx_loop(mlx->ptr);
//     return (EXIT_SUCCESS);
// }