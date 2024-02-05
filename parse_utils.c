#include "parse.h"

static int ft_isdigit(int c)
{
    return (c >= '0' && c <= '9');
}

static int ft_isspace(int c)
{
    return (c == ' ' || (c >= '\t' && c <= '\r'));
}

double ft_pow(double base, int exp)
{
    double result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }
    return result;
}

int ft_atod(const char *str, double *nbr)
{
    double result = 0;
    double fraction = 0.0;
    int divisor = 1;
    bool negative = false;

    while (ft_isspace(*str)) 
        str++; // Skip whitespace

    if (*str == '+' || *str == '-')
    {
        negative = (*str == '-');
        str++;
    }

    while (ft_isdigit(*str))
    {
        result = result * 10.0 + (*str - '0');
        str++;
    }

    if (*str == '.')
    {
        str++;
        while (ft_isdigit(*str))
        {
            fraction = fraction * 10.0 + (*str - '0');
            divisor *= 10;
            str++;
        }
    }

    result += fraction / divisor;

    if (negative)
        result = -result;

    *nbr = result;

    return (str != NULL);
}

void    ft_free_split(char **array)
{
    int i;

    if (!array)
        return;

    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

int parse_vec3(char *str, t_vec3 *vec)
{
    int parsed = 0;
    parsed += ft_atod((const char *)&str, &vec->x) && *str++ == ',';
    parsed += ft_atod((const char *)&str, &vec->y) && *str++ == ',';
    parsed += ft_atod((const char *)&str, &vec->z);
    return (parsed == 3);
}

int validate_orientation(const t_vec3 *orientation)
{
    double len = sqrt(orientation->x * orientation->x + orientation->y * orientation->y + orientation->z * orientation->z);
    if (fabs(len - 1.0) > 1e-6)
        return (0);
    return (1);
}


double parse_fov(char *str)
{
    double fov;
    if (!ft_atod((const char *)&str, &fov) || fov <= 0.0 || fov > 180.0)
        return (-1.0);
    return (fov);
}

int parse_rgb(char **color_parts, t_rgb *color)
{
    for (int i = 0; i < 3; ++i)
    {
        double temp;
        if (!ft_str_to_double(color_parts[i], &temp) || temp < 0 || temp > 255)
        {
            return 0; // Échec de la conversion ou valeur hors limites
        }
        // Assigner les valeurs converties à la structure de couleur
        if (i == 0) color->r = (int)temp;
        if (i == 1) color->g = (int)temp;
        if (i == 2) color->b = (int)temp;
    }
    return 1; // Succès
}


int parse_cylinder_details(char **parts, t_cyl *cyl) {
    if (!parse_vec3(parts[1], &cyl->center) ||
        !parse_vec3(parts[2], &cyl->orientation) ||
        !ft_str_to_double(parts[3], &cyl->diameter) || cyl->diameter <= 0 ||
        !ft_str_to_double(parts[4], &cyl->height) || cyl->height <= 0) {
        return 0;
    }
    return 1;
}

int parse_cylinder_color(char *part, t_cyl *cyl) {
    char **color_parts = ft_split(part, ',');
    int success = parse_rgb(color_parts, &cyl->color);
    ft_free_split(color_parts);
    return success;
}
