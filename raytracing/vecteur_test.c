/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecteur_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:48:04 by alletond          #+#    #+#             */
/*   Updated: 2024/02/21 17:32:12 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "raytracing.h"

typedef struct s_distd
{
    double FOV;
    double width;
}   t_distd;

// bool is_sphere(int width, int height)
// {
//     if ()
// }

int calc_d(t_distd distD)
{
    
    return (0);
}

void throw_ray(t_scene *scene, void *mlx, void *mlx_win)
{
    (void)scene;
    int width = 860;
    int height = 600;
    int x = 0;
    int y = 0;

    while (y < height)
    {
        x = 0;
        while (x < width)
        {
            // if (is_sphere(x , y, scene))
            int color = 0xFFFFFF;
            mlx_pixel_put(mlx, mlx_win, x, y, color);

            x++;
        }
        y++;
    }
}

// int main(int ac, char **av)
// {
//     (void)ac;
//     void *mlx;
//     void *mlx_win;

//     t_scene scene = check_and_fill(av);
//     print_scene(scene);
//     mlx = mlx_init();
//     if (!mlx) return (1);
//     mlx_win = mlx_new_window(mlx, 860, 600, "miniRT");
//     if (!mlx_win) return (1);

//     throw_ray(&scene, mlx, mlx_win);

//     // Entrer dans la boucle mlx pour maintenir la fenêtre ouverte
//     mlx_loop(mlx);

//     return (0);
// }


/*
for y from 0 to height:
    for x from 0 to width:
        // Convertir (x, y) en coordonnées 3D sur le plan de projection
        Point3D pointSurPlan = convertirEn3D(x, y, d, caméra);
        Vecteur3D direction = normaliser(pointSurPlan - positionCaméra);
        
        // Vérifier l'intersection avec la sphère
        if (intersectionRayonSphère(positionCaméra, direction, sphère)):
            color = couleur de la sphère;
        else:
            color = couleur de fond;
        
        // Dessiner le pixel
        mlx_pixel_put(mlx, mlx_win, x, y, color);
*/