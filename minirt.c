#include "parse.h"

int main()
{
    t_camera camera;
    t_light light;
    t_sphere sphere;
    t_plane plane;
    t_amb_light am_light;
    t_cyl cyl;
    
    char *line = "C -50.0,0aaaa,20     0,0,1   70";
    char *line_C = "L -40.0,50.0,0.0 0.6 10,0,255";
    char *line_sp = "sp 199999,0.0,20.6 12.6 10,0,255";
    char *line_pl = "pl 0.0,0.0,-1088888.0 0.0,1.....0,0.0 0,0,225";
    char *line_cy = "cy 50.0,0.0,20.6 0.0,0.0,1.0 1fghj4.2 21.42 10,0,255";
    char *line_am = "A 0.2 255,255,255";

    bool an = parse_ambient_lightning(line_am, &am_light);
    int res_cy = parse_cylinder(line_cy, &cyl);
    int res_sp = parse_sphere(line_sp, &sphere);
    int res_C = parse_camera(line, &camera);
    int res_L = parse_light(line_C, &light);
    int res_pl = parse_plane(line_pl, &plane);
    print_camera(&camera);
    print_cylinder(&cyl);
    printf("%d\n", res_L);
    printf("%d\n", res_C);
    printf("%d\n", res_sp);
    printf("%d\n", res_pl);
    printf("%d\n", res_cy);
    printf("%d\n", an);

    print_plane(&plane);
    print_sphere(&sphere);
    print_light(&light);
}