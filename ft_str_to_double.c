#include "parse.h"

static int ft_isspace(char c) {
    return (c == ' ' || (c >= '\t' && c <= '\r'));
}

static int ft_isdigit(int c) {
    return (c >= '0' && c <= '9');
}

int ft_str_to_double(const char *str, double *nbr) 
{
    double sign = 1.0;
    double result = 0.0;
    int decimal_found = 0;
    int decimal_places = 0;
    int number_found = 0;
    
    while (ft_isspace(*str)) {
        str++;
    }
    
    if (*str == '-' || *str == '+') {
        sign = (*str++ == '-') ? -1.0 : 1.0;
    }
    for (; ft_isdigit(*str) || (!decimal_found && *str == '.'); str++) {
        if (*str == '.') {
            decimal_found = 1;
        } else {
            result = result * 10.0 + (*str - '0');
            if (decimal_found) {
                decimal_places++;
            }
            number_found = 1;
        }
    }
    if (decimal_places > 0) {
        result *= ft_pow(10, -decimal_places);
    }
    *nbr = result * sign;
    
    return number_found;
}