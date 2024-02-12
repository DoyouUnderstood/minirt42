/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:53:45 by alletond          #+#    #+#             */
/*   Updated: 2024/02/12 17:37:39 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void free_object(t_object *obj) 
{
    if (!obj)
        return;

    switch (obj->type) 
    {
        case SPHERE:
            free((t_sphere *)obj->obj);
            break;
        case PLANE:
            free((t_plane *)obj->obj);
            break;
        case CYLINDER:
            free((t_cyl *)obj->obj);
            break;
        case INVALID_TYPE:
            break ;
    }
    free(obj);
}

void free_objects_list(t_obj_list *objects) 
{
    t_object *current = objects->head;
    t_object *next;

    while (current != NULL) {
        next = current->next;
        free_object(current);
        current = next;
    }
}

void free_scene(t_scene *scene) 
{
    free_objects_list(&scene->objects);
}

