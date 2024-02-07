#include "parse.h"

void print_rgb(t_rgb color) {
    printf("RGB Color: (r: %d, g: %d, b: %d)\n", color.r, color.g, color.b);
}

void print_vec3(t_vec3 vec) {
    printf("Vector3: (x: %f, y: %f, z: %f)\n", vec.x, vec.y, vec.z);
}

void print_amb_light(t_amb_light amb) {
    printf("Ambient Light: (Intensity: %f, ", amb.intensity);
    print_rgb(amb.color); // This uses the RGB print function
    printf(")\n");
}

void print_light(t_light light) {
    printf("Light: (Position: ");
    print_vec3(light.position);
    printf(", Brightness: %f, ", light.brightness);
    print_rgb(light.color);
    printf(")\n");
}

void print_camera(t_camera cam) {
    printf("Camera: (Position: ");
    print_vec3(cam.pos);
    printf(", Orientation: ");
    print_vec3(cam.orientation);
    printf(", FOV: %f)\n", cam.fov);
}

void print_plane(t_plane plane) 
{
    printf("Plane: (Center: ");
    print_vec3(plane.center);
    printf(", Orientation: ");
    print_vec3(plane.orientation);
    print_rgb(plane.color);
    printf(")\n");
}

void print_sphere(t_sphere sphere) 
{
    printf("Sphere: (Center: ");
    print_vec3(sphere.center);
    printf(", Diameter: %f, ", sphere.diameter);
    print_rgb(sphere.color);
    printf(")\n");
}

void print_cyl(t_cyl cyl) {
    printf("Cylinder: (Center: ");
    print_vec3(cyl.center);
    printf(", Orientation: ");
    print_vec3(cyl.orientation);
    printf(", Diameter: %f, Height: %f, ", cyl.diameter, cyl.height);
    print_rgb(cyl.color);
    printf(")\n");
}