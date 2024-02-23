#ifndef RAY_H
# define RAY_H

#include "../include/vecteur.h"

typedef struct s_ray 
{
    t_tuple origin;    // L'origine du rayon
    t_tuple direction; // La direction du rayon
} t_ray;

typedef struct 
{
    int count;
    double t[2];
} t_intersections;

#endif 