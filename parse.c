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


int parse_cylinder(char *str, t_cyl *cyl) 
{
    char **parts = ft_split(str, ' ');
    if (!parts) 
        return 0;

    int success = parse_cylinder_details(parts, cyl) &&
                  parse_cylinder_color(parts[5], cyl);
 
    ft_free_split(parts);
    return success ? 1 : 0;
}

int parse_camera(char *line, t_camera *camera)
{
    char    **parts;
    int     valid_parse = 1;

    parts = ft_split(line, ' ');
    if (!parts)
        return (0);

    if (!parse_vec3(parts[1], &camera->pos))
        valid_parse = 0;

    t_vec3 orientation;
    if (valid_parse && parse_vec3(parts[2], &orientation))
    {
        if (!validate_orientation(&orientation))
            valid_parse = 0;
        else
            camera->orientation = orientation;
    }
    else
        valid_parse = 0;

    double fov;
    if (valid_parse && ft_str_to_double(parts[3], &fov))
    {
        if (fov <= 0.0 || fov > 180.0)
            valid_parse = 0;
        else
            camera->fov = fov;
    }
    else
        valid_parse = 0;
    ft_free_split(parts);
    return (valid_parse);
}

int parse_plane(char *str, t_plane *plane)
{
    char **parts = ft_split(str, ' ');
    if (!parts || !parts[1] || !parts[2] || !parts[3])
        return 0; // Validation basique et échec du split

    if (!parse_vec3(parts[1], &plane->center) ||
        !parse_vec3(parts[2], &plane->orientation))
    {
        ft_free_split(parts); // Libération de la mémoire en cas d'échec
        return 0;
    }

    if (!rgb(parts[3], &plane->color))
    {
        ft_free_split(parts); 
        return 0;
    }

    ft_free_split(parts);
    return 1; // Succès
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

    if (!ft_str_to_double(parts[2], &sphere->diameter) || sphere->diameter <= 0.0)
    {
        ft_free_split(parts);
        return 0;
    }
    char **color_parts = ft_split(parts[3], ',');
    for (int i = 0; i < 3; ++i)
    {
        double temp;
        if (!ft_str_to_double(color_parts[i], &temp) || temp < 0 || temp > 255)
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

int parse_light(char *str, t_light *light)
{
    char **parts = ft_split(str, ' ');
    if (!parts)
        return 0;

    if (!parse_vec3(parts[1], &light->position))
    {
        ft_free_split(parts);
        return 0;
    }

    if (!ft_str_to_double(parts[2], &light->brightness) || light->brightness < 0.0 || light->brightness > 1.0)
    {
        ft_free_split(parts);
        return 0;
    }

    char **color_parts = ft_split(parts[3], ',');
    for (int i = 0; i < 3; ++i)
    {
        double temp;
        if (!ft_str_to_double(color_parts[i], &temp) || temp < 0 || temp > 255)
        {
            ft_free_split(parts);
            ft_free_split(color_parts);
            return 0;
        }
        light->color[i] = (int)temp;
    }

    ft_free_split(parts);
    ft_free_split(color_parts);
    return 1;
}
