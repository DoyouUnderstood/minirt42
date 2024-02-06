#include "parse.h"

void print_vec3(t_vec3 vec)
{
    printf("x: %f, y: %f, z: %f", vec.x, vec.y, vec.z);
}

void print_camera(const t_camera *camera)
{
    printf("Camera:\n");
    printf(" Position: ");
    print_vec3(camera->pos);
    printf("\n Orientation: ");
    print_vec3(camera->orientation);
    printf("\n FOV: %f\n", camera->fov);
}

void print_light(const t_light *light)
{
    printf("Light:\n");
    print_vec3(light->position);
    printf("\nBrightness: %.2f\n", light->brightness);
}

void print_sphere(const t_sphere *sphere)
{
    printf("Sphere:\n");
    printf(" Center: (%.2f, %.2f, %.2f)\n", sphere->center.x, sphere->center.y, sphere->center.z);
    printf(" Diameter: %.2f\n", sphere->diameter);
    printf(" Color: (R: %d, G: %d, B: %d)\n", sphere->color[0], sphere->color[1], sphere->color[2]);
}

void print_rgb(const t_rgb *color)
{
    printf("(R: %d, G: %d, B: %d)", color->r, color->g, color->b);
}

void print_plane(const t_plane *plane)
{
    printf("Plane:\n");
    printf(" Center: ");
    print_vec3(plane->center);
    printf("\n Orientation: ");
    print_vec3(plane->orientation);
    printf("\n Color: ");
    print_rgb(&plane->color);
    printf("\n");
}

void print_cylinder(const t_cyl *cyl) {
    printf("Cylinder:\n");
    printf(" Center: ");
    print_vec3(cyl->center);
    printf("\n Orientation: ");
    print_vec3(cyl->orientation);
    printf("\n Diameter: %.2f", cyl->diameter);
    printf("\n Height: %.2f", cyl->height);
    printf("\n ");
    print_rgb(&cyl->color);
    printf("\n");
}

