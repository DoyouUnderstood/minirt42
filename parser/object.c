
#include "../include/parse.h"

void add_object(t_obj_list *list, void *obj, t_obj_type type) 
{
    t_object *current;
    t_object *new_object = malloc(sizeof(t_object));
    if (!new_object) 
       error_exit("Error allocate object minirt.c l 32 \n");
    new_object->type = type;
    new_object->obj = obj;
    new_object->next = NULL;

    if (list->head == NULL)
        list->head = new_object;
    else 
    {
        current = list->head;
        while (current->next != NULL)
            current = current->next;
        current->next = new_object;
    }
}

void *allocate_object(char **ptr, t_obj_type type) 
{
    if (type == SPHERE) 
    {
        t_sphere *obj = malloc(sizeof(t_sphere));
        if (obj) 
            parse_sphere(ptr, obj);
        return (obj);
    } 
    else if (type == PLANE) 
    {
        t_plane *obj = malloc(sizeof(t_plane));
        if (obj) 
            parse_plane(ptr, obj);
        return (obj);
    } else if (type == CYLINDER) 
    {
        t_cyl *obj = malloc(sizeof(t_cyl));
        if (obj) 
            parse_cylinder(ptr, obj);
        return (obj);
    }
    return (NULL);
}

t_obj_type get_object_type(char *identifier) 
{
    if (!strncmp(identifier, "sp", 2)) 
        return (SPHERE);
    else if (!strncmp(identifier, "pl", 2)) 
        return (PLANE);
    else if (!strncmp(identifier, "cy", 2)) 
        return (CYLINDER);
    else 
        return (INVALID_TYPE);
}

void parse_object(char **ptr, t_obj_list *objects) 
{
    t_obj_type type = get_object_type(ptr[0]);
    if (type != INVALID_TYPE)
    {
        void *obj = allocate_object(ptr, type);
        if (obj)
            add_object(objects, obj, type);
        else
            error_exit("failed to allocate object\n");
    } else 
        error_exit("failed to create object, this is not good type buddy \n");
}