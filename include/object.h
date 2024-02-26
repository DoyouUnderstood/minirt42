#ifndef OBJECT_H
#define OBJECT_H
#include "parse.h"

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
	t_tuple			center;
	t_tuple			orientation;
	t_rgb			color;
}					t_plane;

typedef struct s_sphere
{
	t_tuple			center;
	double			diameter;
	t_rgb			color;
}					t_sphere;

typedef struct s_cyl
{
	t_tuple			center;
	t_tuple			orientation;
	double			diameter;
	double			height;
	t_rgb			color;
}					t_cyl;

#endif 