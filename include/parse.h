#include "../lib/GNL/get_next_line.h"
#include "../lib/libft/libft.h"
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../lib/mlx/mlx.h"
#include <math.h>

typedef struct s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct s_amb_light
{
	double			intensity;
	t_rgb			color;
}					t_amb_light;

typedef struct s_light
{
	t_vec3			position;
	double			brightness;
	t_rgb			color;
}					t_light;

typedef struct s_camera
{
	t_vec3			pos;
	t_vec3			orientation;
	double			fov;
}					t_camera;

typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	INVALID_TYPE = -1,
}					t_obj_type;

typedef struct s_object
{
	t_obj_type		type;
	void			*obj;
	struct s_object	*next;
}					t_object;

typedef struct s_obj_list
{
	t_object *head;
}					t_obj_list;

typedef struct s_plane
{
	t_vec3			center;
	t_vec3			orientation;
	t_rgb			color;
}					t_plane;

typedef struct s_sphere
{
	t_vec3			center;
	double			diameter;
	t_rgb			color;
}					t_sphere;

typedef struct s_cyl
{
	t_vec3			center;
	t_vec3			orientation;
	double			diameter;
	double			height;
	t_rgb			color;
}					t_cyl;

typedef struct s_scene
{
	t_amb_light		amb_light;
	t_light			spot_light;
	t_camera		camera;
	t_obj_list		objects;
}					t_scene;

/* =========== Parseur ========== */

void				parse_cylinder(char **str, t_cyl *cyl);
void				parse_camera(char **line, t_camera *camera);
void				parse_plane(char **str, t_plane *plane);
void				parse_sphere(char **str, t_sphere *sphere);
void				parse_light(char **str, t_light *light);
void				parse_ambient_lightning(char **str, t_amb_light *light);
t_scene				parse(char **str);
void parse_object(char **ptr, t_obj_list *objects);

/* =========== Parseur utils ========== */

void				error_exit(const char *error);
bool				in_range(double start, double end, double value);
double				ft_strtod(char *s);
bool				valid_bright(double bright);
int					ft_atod(const char *str, double *nbr);
void				ft_free_split(char **array);
int					parse_vec3(char *str, t_vec3 *vec);
int					validate_orientation(const t_vec3 *orientation);
double				parse_fov(char *str);
char				**ft_split(char const *s, char c);
double				ft_pow(double base, int exp);
void				rgb(char *str, t_rgb *color);
char				*advance_to_next_component(char **str);

/* =========== FREE ========== */

void				free_split(char **parts);
void				free_scene(t_scene *scene);

/* =========== Print ============ */

void				print_scene(t_scene scene);
void				ft_print_double_array(char **arr);
