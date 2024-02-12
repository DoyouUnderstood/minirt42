#include "parse.h"

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

bool valid_bright(double bright)
{
    if (bright >= 0 && bright <= 1)
        return (true);
    return (false);
}

char *advance_to_next_component(char **str) 
{
    while (**str && **str != ',') 
        (*str)++;
    if (**str == ',') 
    {
        (*str)++;
        return *str;
    } else
        return (NULL);
}

void	error_exit(const char *error)
{
	printf("Error: %s\n", error);
	exit(EXIT_FAILURE);
}