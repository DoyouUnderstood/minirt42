#include "parse.h"


bool in_range(double start, double end, double value)
{
    return (value >= start && value <= end);
}

int ft_atoi_rgb(char **str)
{
    int res = 0;
    while (**str >= '0' && **str <= '9')
    {
        res = res * 10 + (**str - '0');
        (*str)++;
    }
    return (res);
}

bool parse_rgb(char **str, int *value)
{
    if (**str == '\0' || (**str == ',' && *(*str + 1) == '\0'))
        return (false);
    *value = ft_atoi_rgb(str);
    if (**str == ',')
        (*str)++;
    return (true);
}

bool rgb(char *str, t_rgb *color)
{
    int r;
    int g;
    int b;

    if (!parse_rgb(&str, &r) || !in_range(0, 255, r))
        return (false);
    if (!parse_rgb(&str, &g) || !in_range(0, 255, g))
        return (false);
    if (!parse_rgb(&str, &b) || !in_range(0, 255, b))
        return (false);
    if (*str != '\0')
        return (false);
    
    color->r = r;
    color->g = g;
    color->b = b;
    return (true);
}


bool ambient_check(char **str, double *intensity) 
{
    ft_atod(*str, intensity);
    if (!in_range(0.0, 1.0, *intensity)) {
        return false;
    }
    return true;
}


bool parse_ambient_lightning(char **str, t_amb_light *light) 
{
    if (!ambient_check(&str[1], &(light->intensity))) {
        return false;
    }
    if (!rgb(str[2], &(light->color))) {
        return false;
    }
    return true;
}

