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
    return NULL; // Aucun objet du type spécifié n'a été trouvé
}

// Calcule le point le long du rayon à la distance t
// Cela se fait en multipliant la direction du rayon par t et en ajoutant le résultat à l'origine du rayon
t_tuple position(t_ray ray, double t) {

    t_tuple movement = multiply_tuple(ray.direction, t);
    t_tuple pos = add_tuples(ray.origin, movement);
    return pos;
}


bool intersect_ray_sphere(t_ray *ray, t_sphere *sphere, double *t) {
    t_tuple sphere_to_ray = subtract_tuples(ray->origin, sphere->center);
    double a = dot(ray->direction, ray->direction);
    double b = 2 * dot(ray->direction, sphere_to_ray);
    double c = dot(sphere_to_ray, sphere_to_ray) - pow(sphere->diameter / 2, 2.0); // Correction ici
    double discriminant = b*b - 4*a*c;

    if (discriminant < 0) {
        return false; // Pas d'intersection
    }

    double t0 = (-b - sqrt(discriminant)) / (2*a);
    double t1 = (-b + sqrt(discriminant)) / (2*a);

    double t_near = t0 < t1 ? t0 : t1;
    if (t_near < 0) t_near = t0 < t1 ? t1 : t0; // Prend l'autre t si t_near est négatif
    if (t_near < 0) return false; // Si t_near est toujours négatif, pas de hit

    *t = t_near;
    return true;
}




void throw_ray(t_sphere *sphere, void *mlx, void *mlx_win) {
    int width = 860;
    int height = 600;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Créer un rayon pour le pixel actuel
            t_tuple origin = point(0, 0, 0); // Supposons que la caméra est à l'origine
            t_tuple direction = normalize_tuple(vector(x - width / 2, y - height / 2, 100)); // Direction simplifiée
            t_ray ray = {origin, direction};

            double t = 0;
            if (intersect_ray_sphere(&ray, sphere, &t)) {
                // Si le rayon intersecte la sphère, colorier le pixel en rouge
                mlx_pixel_put(mlx, mlx_win, x, y, 0xFF0000);
            } else {
                // Sinon, le pixel reste noir ou la couleur de fond
                mlx_pixel_put(mlx, mlx_win, x, y, 0x000000);
            }
        }
    }
}



int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    void *mlx;
    void *mlx_win;
    mlx = mlx_init();
    if (!mlx) return (1);
    mlx_win = mlx_new_window(mlx, 860, 600, "miniRT");
    if (!mlx_win) 
        return (1);
    t_sphere sp = {
    .center = {350, 250, 170, 1.0}, // Assumant que w=1.0 est approprié ici pour un point
    .diameter = 150,
    .color = {255, 0, 0}
    };

        throw_ray(&sp, mlx, mlx_win);

    mlx_hook(mlx_win, 17, 0L, close_window, mlx);
    mlx_loop(mlx);
    mlx_cleanup(mlx);
    return (0);
}
