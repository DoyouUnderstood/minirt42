#include "parse.h"

double str_to_double(const char *str) 
{
    if (str == NULL) {
        return 0.0;
    }

    char *copy = strdup(str);
    if (copy == NULL) {
        return 0.0;
    }

    for (char *p = copy; *p; p++) {
        if (*p == ',') {
            *p = '.';
        }
    }

    double result = ft_strtod(copy);
    free(copy);
    return (result);
}
