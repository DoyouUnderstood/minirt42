#include "../include/mlxinit.h"

#define KEY_ESC 0xff1b

int handle_keypress(int keysym, t_mlx *mlx)
{
    if (keysym == KEY_ESC)
    {
        mlx_cleanup(mlx);
        exit(0);
    }
    return (0);
}

int close_window(t_mlx *mlx)
{
    mlx_destroy_window(mlx->ptr, mlx->win);
    exit(0);
    return (0);
}


