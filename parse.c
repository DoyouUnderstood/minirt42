#include "parse.h"

// int parse_all()
// {
//     t_camera camera;
//     t_light light;
//     t_sphere sphere;
//     t_plane plane;
//     t_cyl cyl; 

//     if (!parse_cylinder(line_cy, &cyl)
//         || !parse_sphere(line_sp, &sphere)
//         || !parse_camera(line, &camera)
//         || !parse_light(line_C, &light)
//         || !parse_plane(line_pl, &plane))
// }


// int parse_cylinder(char *str, t_cyl *cyl) 
// {
//     char **parts = ft_split(str, ' ');
//     if (!parts) 
//         return 0;

//     int success = parse_cylinder_details(parts, cyl) &&
//                   parse_cylinder_color(parts[5], cyl);
 
//     ft_free_split(parts);
//     return success ? 1 : 0;
// }

bool parse_camera(char **parts, t_camera *camera)
{
    double fov;
    t_vec3 orientation;
    if (!parse_vec3(parts[1], &camera->pos))
        return (false);
    if (!parse_vec3(parts[2], &orientation))
       return (false);
    else
        camera->orientation = orientation;
    fov = str_to_double(parts[3]);
    if (!in_range(0, 70, fov))
        return (false);
    else
        camera->fov = fov;
    return (true);
}

int parse_vec3(char *str, t_vec3 *vec) {
    int count = 0;
    char *next;

    vec->x = ft_strtod(str);
    next = advance_to_next_component(&str);
    if (!next) return 0;
    count++;

    vec->y = ft_strtod(str);
    next = advance_to_next_component(&str);
    if (!next) return 0;
    count++;

    vec->z = ft_strtod(str);
    while (*str) {
        if (*str == ',')
            return 0;
    }
    count++;
    return (count == 3);
}



bool parse_plane(char **parts, t_plane *plane)
{
    if (!parse_vec3(parts[1], &plane->center) ||
        !parse_vec3(parts[2], &plane->orientation))
        return (false);

    if (!rgb(parts[3], &plane->color))
        return (false);

    return (true);
}

int parse_sphere(char *str, t_sphere *sphere)
{
    char **parts = ft_split(str, ' ');
    if (!parts)
        return 0; 

    if (!parse_vec3(parts[1], &sphere->center))
    {
        ft_free_split(parts);
        return 0;
    }

    if (!ft_atod(parts[2], &sphere->diameter) || sphere->diameter <= 0.0)
    {
        ft_free_split(parts);
        return 0;
    }
    char **color_parts = ft_split(parts[3], ',');
    for (int i = 0; i < 3; ++i)
    {
        double temp;
        if (!ft_atod(color_parts[i], &temp) || temp < 0 || temp > 255)
        {
            ft_free_split(parts);
            ft_free_split(color_parts);
            return 0;
        }
        sphere->color[i] = (int)temp;
    }

    ft_free_split(parts);
    ft_free_split(color_parts);
    return 1;
}

bool parse_light(char **parts, t_light *light)
{
    if (!parse_vec3(parts[1], &light->position))
        return (false);
    if (!ft_atod(parts[2], &light->brightness))
        return (false);
    if (!valid_bright(light->brightness))
        return (false);
    if (!rgb(parts[3], &light->color))
        return (false);
    return (true);
}
