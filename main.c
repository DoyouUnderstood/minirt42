#include "parse.h"


/*          A FAIRE 

    !!!!    Verifier les intputs et les stockers dans les structs. !!!!

    fonctions parse_all qui va appeller toute 
    les fonctions specifique au objet present dans minirt.rt (parseA, parseC,
    parseL, etc ..)

    faire les fonctions specifique.
    faire les fonctions qui verifie l'ambien light. le rbg .les coord xyz etc .
    stocker toute les infos 

*/


int is_delimiter(char c, const char *delimiters) 
{
    while (*delimiters) {
        if (c == *delimiters) {
            return 1;
        }
        delimiters++;
    }
    return 0;
}

void skip_to_next(char **str, const char *delimiters) 
{
    while (**str && !is_delimiter(**str, delimiters)) {
        (*str)++;
    }
}

void skip_space(char **str)
{
    while (**str && **str == ' ')
        (*str)++;
}


static bool in_range(double start, double end, double value)
{
    return (value >= start && value <= end);
}

static int ft_atoi_rgb(char **str)
{
    int res = 0;
    while (**str >= '0' && **str <= '9')
    {
        res = res * 10 + (**str - '0');
        (*str)++;
    }
    return (res);
}

static bool parse_rgb(char **str, int *value)
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

    if (!parse_rgb(&str, &r) || !in_range(r, 0, 255))
        return (false);
    if (!parse_rgb(&str, &g) || !in_range(g, 0, 255))
        return (false);
    if (!parse_rgb(&str, &b) || !in_range(b, 0, 255))
        return (false);
    if (*str != '\0')
        return (false);
    
    color->r = r;
    color->g = g;
    color->b = b;
    return (true);
}


bool ambient_check(char **str, double *intensity) {
    // Utilisation hypothétique de ft_atod pour lire l'intensité
    ft_atod(*str, intensity); // Supposons que cela ne modifie pas *str directement

    // Avance manuellement *str pour trouver le début des données RGB
    while (**str && **str != ' ' && **str != ',') 
        (*str)++;
    if (**str) 
        (*str)++; // Avance au-delà de l'espace ou de la virgule trouvé

    // Vérification de l'intensité
    if (!in_range(0.0, 1.0, *intensity)) {
        return false;
    }
    
    return true;
}


bool parse_ambient_lightning(char *str, t_amb_light *light) 
{
    skip_to_next(&str, " ");
    if (!ambient_check(&str, &(light->intensity))) {
        return false;
    }
    skip_to_next(&str, " ");
    printf("string :%s\n", str);
    if (!rgb(str, &(light->color))) {
        return false;
    }
    return true;
}

