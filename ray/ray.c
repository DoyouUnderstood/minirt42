#include <stdio.h>
#include "../include/ray.h"

// Fonction pour initialiser un rayon
t_ray create_ray(t_tuple origin, t_tuple direction) {
    t_ray ray;
    ray.origin = origin;
    ray.direction = direction;
    return ray;
}

// Fonction pour afficher un rayon
void print_ray(t_ray ray) {
    printf("Ray Origin: (%.2f, %.2f, %.2f)\n", ray.origin.x, ray.origin.y, ray.origin.z);
    printf("Ray Direction: (%.2f, %.2f, %.2f)\n", ray.direction.x, ray.direction.y, ray.direction.z);
}

// Fonction pour calculer le point à la distance t le long du rayon
t_tuple position(t_ray ray, double t) 
{
    t_tuple displacement = multiply_tuple(ray.direction, t);
    return add_tuples(ray.origin, displacement);
}

t_tuple vec3_to_tuple(t_vec3 v) {
    return (t_tuple){v.x, v.y, v.z, 0.0}; // Supposons que c'est un vecteur, donc w=0.0
}

t_vec3 tuple_to_vec3(t_tuple t) {
    // Note : Cette fonction ignore la composante w, car t_vec3 n'a pas de champ w.
    return (t_vec3){t.x, t.y, t.z};
}

// Cette fonction calcule les intersections d'un rayon avec une sphère, avec un traitement spécial pour les cas tangentiels.
// Dans ces cas, elle renvoie deux fois le même point d'intersection pour simplifier la gestion des chevauchements d'objets.

t_intersections intersect_with_tangent_handling(t_sphere sphere, t_ray ray) 
{
    t_vec3 ray_dir = tuple_to_vec3(ray.direction);
    t_vec3 ray_or = tuple_to_vec3(ray.origin);
    t_vec3 sphere_to_ray = subtract_vectors(ray_or, sphere.center);
    double a = dot(ray_dir, ray_dir);
    double b = 2 * dot(ray_dir, sphere_to_ray);
    double c = dot(sphere_to_ray, sphere_to_ray) - pow(sphere.diameter / 2, 2);

    double discriminant = b * b - 4 * a * c;
    t_intersections intersections;
    intersections.count = 0;

    if (discriminant >= 0) {
        double sqrt_discriminant = sqrt(discriminant);
        double t1 = (-b - sqrt_discriminant) / (2 * a);
        double t2 = (-b + sqrt_discriminant) / (2 * a);
        intersections.count = 2; // Assurez-vous de renvoyer deux fois la même valeur pour le cas tangentiel
        intersections.t[0] = t1;
        intersections.t[1] = t2;
}

    return intersections;
}

// Fonction pour calculer les intersections d'un rayon avec une sphère
t_intersections intersect(t_sphere sphere, t_ray ray) 
{
    // Convertir l'origine du rayon et la direction en t_vec3 si nécessaire
    t_vec3 ray_origin_vec3 = tuple_to_vec3(ray.origin);
    t_vec3 ray_direction_vec3 = tuple_to_vec3(ray.direction);
    t_vec3 sphere_center_vec3 = sphere.center; // Supposons que sphere.center est déjà un t_vec3

    // Calculer le vecteur du centre de la sphère à l'origine du rayon
    t_vec3 sphere_to_ray = subtract_vectors(ray_origin_vec3, sphere_center_vec3);
    
    double a = dot(ray_direction_vec3, ray_direction_vec3);
    double b = 2 * dot(ray_direction_vec3, sphere_to_ray);
    double c = dot(sphere_to_ray, sphere_to_ray) - pow(sphere.diameter / 2, 2);

    double discriminant = b * b - 4 * a * c;
    t_intersections intersections;
    intersections.count = 0;

    if (discriminant >= 0) {
        double sqrt_discriminant = sqrt(discriminant);
        intersections.t[0] = (-b - sqrt_discriminant) / (2 * a);
        intersections.t[1] = (-b + sqrt_discriminant) / (2 * a);
        intersections.count = (discriminant > 0) ? 2 : 1;
    }

    return intersections;
}

t_intersections intersect_sphere_behind_ray(t_sphere sphere, t_ray ray) 
{
    t_vec3 sphere_to_ray = subtract_vectors(tuple_to_vec3(ray.origin), sphere.center);
    double a = dot(tuple_to_vec3(ray.direction), tuple_to_vec3(ray.direction));
    double b = 2.0 * dot(tuple_to_vec3(ray.direction), sphere_to_ray);
    double c = dot(sphere_to_ray, sphere_to_ray) - pow(sphere.diameter / 2, 2);

    double discriminant = b * b - 4 * a * c;
    t_intersections intersections;
    intersections.count = 0;

    if (discriminant >= 0) {
        double sqrt_discriminant = sqrt(discriminant);
        intersections.t[0] = (-b - sqrt_discriminant) / (2 * a);
        intersections.t[1] = (-b + sqrt_discriminant) / (2 * a);
        // Assurez-vous que les intersections sont triées
        if (intersections.t[0] > intersections.t[1]) {
            double temp = intersections.t[0];
            intersections.t[0] = intersections.t[1];
            intersections.t[1] = temp;
        }
        intersections.count = 2;
    }

    return intersections;
}

t_intersections intersect_sphere_from_inside(t_sphere sphere, t_ray ray) {
    t_vec3 sphere_to_ray = subtract_vectors(tuple_to_vec3(ray.origin), sphere.center);
    double a = dot(tuple_to_vec3(ray.direction), tuple_to_vec3(ray.direction));
    double b = 2.0 * dot(tuple_to_vec3(ray.direction), sphere_to_ray);
    double c = dot(sphere_to_ray, sphere_to_ray) - pow(sphere.diameter / 2, 2);

    double discriminant = b * b - 4 * a * c;
    t_intersections intersections;
    intersections.count = 0;

    if (discriminant >= 0) {
        double sqrt_discriminant = sqrt(discriminant);
        intersections.t[0] = (-b - sqrt_discriminant) / (2 * a);
        intersections.t[1] = (-b + sqrt_discriminant) / (2 * a);
        intersections.count = 2;
    }

    return intersections;
}


t_intersections intersect_sphere(t_sphere sphere, t_ray ray) 
{
    t_intersections intersections;
    t_vec3 ray_origin_vec3 = tuple_to_vec3(ray.origin);
    t_vec3 ray_direction_vec3 = tuple_to_vec3(ray.direction);
    t_vec3 sphere_to_ray = subtract_vectors(ray_origin_vec3, sphere.center);
    double a = dot(ray_direction_vec3, ray_direction_vec3);
    double b = 2.0 * dot(ray_direction_vec3, sphere_to_ray);
    double c = dot(sphere_to_ray, sphere_to_ray) - pow(sphere.diameter / 2, 2);
    double discriminant = b * b - 4 * a * c;
    intersections.count = 0;

    // si c le rateyy
    if (discriminant < 0) {
        return intersections;
    }

    // Si le discriminant est >= 0, calculez les points d'intersection
    double sqrt_discriminant = sqrt(discriminant);
    intersections.t[0] = (-b - sqrt_discriminant) / (2 * a);
    intersections.t[1] = (-b + sqrt_discriminant) / (2 * a);
    intersections.count = discriminant == 0 ? 1 : 2;

    return (intersections);
}


int main() {
    t_tuple origin = point(2, 3, 4); // Origine du rayon
    t_tuple direction = vector(1, 0, 0); // Direction du rayon
    t_ray ray = {origin, direction}; // Création du rayon

    t_tuple pos0 = position(ray, 0); // Point à la distance 0
    t_tuple pos1 = position(ray, 1); // Point à la distance 1
    t_tuple posNeg1 = position(ray, -1); // Point à la distance -1
    t_tuple pos2_5 = position(ray, 2.5); // Point à la distance 2.5

    printf("Position à t=0 : (%.2f, %.2f, %.2f)\n", pos0.x, pos0.y, pos0.z);
    printf("Position à t=1 : (%.2f, %.2f, %.2f)\n", pos1.x, pos1.y, pos1.z);
    printf("Position à t=-1 : (%.2f, %.2f, %.2f)\n", posNeg1.x, posNeg1.y, posNeg1.z);
    printf("Position à t=2.5 : (%.2f, %.2f, %.2f)\n", pos2_5.x, pos2_5.y, pos2_5.z);
    return 0;
}