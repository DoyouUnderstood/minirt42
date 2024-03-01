#include "../include/object.h"
#include "../include/ray.h"

typedef struct s_inter 
{
    double t;
    t_object *object;
}t_intersection;

typedef struct s_list_inter
{
    t_intersection inter;
    struct s_list_inter *next;
}               t_list_inter;

void add_intersection(t_list_inter **list, t_intersection inter) {
    t_list_inter *new_element = (t_list_inter *)malloc(sizeof(t_list_inter));
    if (!new_element) 
        return; // Gestion d'erreur en cas d'échec de malloc
    new_element->inter = inter;
    new_element->next = *list;
    *list = new_element;
}

t_list_inter *intersections(t_intersection inter1, t_intersection inter2) {
    t_list_inter *list = NULL;
    add_intersection(&list, inter1);
    add_intersection(&list, inter2);
    return list;
}

//fonction pour créer une intersection
t_intersection create_intersection(double t, t_object *object) 
{
    t_intersection intersection;

    intersection.t = t;
    intersection.object = object;
    return (intersection);
}

t_list_inter *intersect_sphere(t_object *object, t_ray *ray) 
{
    t_list_inter *intersections = NULL;
    double t1, t2;

    if (object->type != SPHERE) return NULL;

    if (intersect_ray_sphere(ray, (t_sphere *)object->obj, &t1, &t2)) {
        if (t1 > 0) {
            t_intersection inter1 = create_intersection(t1, object);
            add_intersection(&intersections, inter1);
        }
        if (t2 > 0 && t2 != t1) {
            t_intersection inter2 = create_intersection(t2, object);
            add_intersection(&intersections, inter2);
        }
    }

    return intersections;
}

/*
La fonction hit doit parcourir la liste d'intersections retournée par intersect_sphere
et sélectionner celle avec la plus petite valeur de t positive, 
car c'est cette intersection qui représente le point le plus proche visible par la caméra.
*/
t_intersection *hit(t_list_inter *intersections) {
    t_intersection *closest_hit = NULL;

    while (intersections != NULL) {
        if (intersections->inter.t > 0 && (closest_hit == NULL || intersections->inter.t < closest_hit->t)) {
            closest_hit = &(intersections->inter);
        }
        intersections = intersections->next;
    }

    return closest_hit;
}
