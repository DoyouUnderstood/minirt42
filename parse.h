#include <stdio.h> 
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct s_rgb
{
    int r;
    int g;
    int b;
} t_rgb;


typedef struct s_vec3
{
    double x;
    double y;
    double z;
} t_vec3;

typedef struct s_amb_light
{
    double intensity;
    t_rgb color;
} t_amb_light;

typedef struct s_light
{
    t_vec3 position;
    double brightness;
    t_rgb color;
} t_light;

typedef struct s_camera
{
    t_vec3 pos;
    t_vec3 orientation;
    double fov;
} t_camera;


typedef enum e_obj_type
{
    SPHERE,
    PLANE,
    CYLINDER,
} t_obj_type;

typedef struct s_object
{
    t_obj_type type;
    void *obj;
    struct s_object *next;
} t_object;

typedef struct s_obj_list
{
    t_object *head; // Pointeur vers le premier objet de la liste
} t_obj_list;

typedef struct s_plane
{
    t_vec3 center;
    t_vec3 orientation;
    t_rgb color;
} t_plane;

typedef struct s_sphere
{
    t_vec3 center;
    double diameter;
    int color[3];
} t_sphere;

typedef struct s_cyl
{
    t_vec3 center;
    t_vec3 orientation;
    double diameter;
    double height;
    t_rgb color;

} t_cyl;


typedef struct s_scene
{
    t_amb_light amb_light;
    t_light spot_light;
    t_camera camera;
    t_obj_list objects;
} t_scene;


/* =========== Print ============ */
void print_camera(const t_camera *camera);
void print_vec3(t_vec3 vec);
void print_light(const t_light *light);
void print_sphere(const t_sphere *sphere);
void print_plane(const t_plane *plane);
void print_cylinder(const t_cyl *cyl);
void ft_print_double_array(char **ptr);



/* =========== Parseur ========== */
int parse_cylinder(char *str, t_cyl *cyl);
bool parse_camera(char **line, t_camera *camera);
int parse_plane(char *str, t_plane *plane);
int parse_sphere(char *str, t_sphere *sphere);
bool parse_light(char **str, t_light *light);
bool parse_ambient_lightning(char **str, t_amb_light *light);

/* =========== Parseur utils ========== */

double	ft_strtod(char *s);
bool valid_bright(double bright);
int ft_atod(const char *str, double *nbr);
void    ft_free_split(char **array);
int parse_vec3(char *str, t_vec3 *vec);
int validate_orientation(const t_vec3 *orientation);
double parse_fov(char *str);
char    **ft_split(char const *s, char c);
double ft_pow(double base, int exp);
double str_to_double(const char *str);
bool rgb(char *str, t_rgb *color);
int parse_cylinder_details(char **parts, t_cyl *cyl);
// int parse_cylinder_color(char *part, t_cyl *cyl);