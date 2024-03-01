/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecteur_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:48:04 by alletond          #+#    #+#             */
/*   Updated: 2024/03/01 13:28:41 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vecteur.h"
#include "../include/parse.h"
#include "raytracing.h"
#include "../include/mlxinit.h"
#include "../include/matrix.h"

typedef struct s_ray {
    t_tuple origin;
    t_tuple direction;
} t_ray;


void* find_first_object_of_type(t_obj_list *obj_list, t_obj_type type) {
    t_object *current = obj_list->head;
    while (current != NULL) {
        if (current->type == type) {
            return current->obj; // Retourne un pointeur vers l'objet trouvé
        }
        current = current->next;
    }
    return (NULL);
}

// Calcule le point le long du rayon à la distance t
// Cela se fait en multipliant la direction du rayon par t et en ajoutant le résultat à l'origine du rayon
t_tuple position(t_ray ray, double t) {

    t_tuple movement = multiply_tuple(ray.direction, t);
    t_tuple pos = add_tuples(ray.origin, movement);
    return pos;
}


bool intersect_ray_sphere(t_ray *ray, t_sphere *sphere, double *t_out1, double *t_out2) 
{
    t_tuple sphere_to_ray = subtract_tuples(ray->origin, sphere->center);
    double a = dot(ray->direction, ray->direction);
    double b = 2 * dot(ray->direction, sphere_to_ray);
    double c = dot(sphere_to_ray, sphere_to_ray) - pow(sphere->diameter / 2, 2.0); // Correction ici
    double discriminant = b*b - 4*a*c;

   if (discriminant < 0) {
        return false; // Pas d'intersection
    }
    *t_out1 = (-b - sqrt(discriminant)) / (2*a);
    *t_out2 = (-b + sqrt(discriminant)) / (2*a);

    return (true);
}

void throw_ray(t_sphere *sphere, void *mlx, void *mlx_win) {
    int width = 860;
    int height = 600;
    double t1, t2;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            t_tuple origin = point(0, 0, 0);
            t_tuple direction = normalize_tuple(vector(x - width / 2, y - height / 2, 100)); // Direction simplifiée
            t_ray ray = {origin, direction};

            t1 = t2 = 0;
            if (intersect_ray_sphere(&ray, sphere, &t1, &t2))
                mlx_pixel_put(mlx, mlx_win, x, y, 0xFF0000);
            else
                mlx_pixel_put(mlx, mlx_win, x, y, 0x000000);
        }
    }
}

t_ray transform(t_ray ray, Matrice4x4 mat) {
    t_ray transformed_ray;

    // Applique la transformation à l'origine du rayon
    transformed_ray.origin = multiplyMatrixByTuple(mat, ray.origin);

    // Applique la transformation à la direction du rayon
    transformed_ray.direction = multiplyMatrixByTuple(mat, ray.direction);

    return transformed_ray;
}



int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    void *mlx;
    void *mlx_win;
    mlx = mlx_init();
    if (!mlx) 
        return (1);
    mlx_win = mlx_new_window(mlx, 860, 600, "miniRT");
    if (!mlx_win) 
        return (1);
    t_sphere sp = 
    {
        .center = {350, 250, 170, 1.0}, // Assumant que w=1.0 est approprié ici pour un point
        .diameter = 150,
        .color = {255, 0, 0}
    };
    throw_ray(&sp, mlx, mlx_win);
    mlx_hook(mlx_win, 17, 0L, close_window, mlx);
    mlx_loop(mlx);
    //mlx_cleanup(mlx);
    return (0);
}


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