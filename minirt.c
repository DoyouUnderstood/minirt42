#include "parse.h"

char    *read_file_into_str(const char *str)
{
    int fd;
    char	*line;
	char	*temp;
	char	*file_content;

    fd = open(str, O_RDONLY);
    if (fd == -1)
        error_exit("Error open filen\n");
	file_content = ft_strdup("");
	line = get_next_line(fd);
	while (line != NULL)
	{
		temp = ft_strjoin(file_content, line);
		free(file_content);
		free(line);
		file_content = temp;
		line = get_next_line(fd);
	}
	return (file_content);
}

void add_object(t_obj_list *list, void *obj, t_obj_type type) 
{
    t_object *current;
    t_object *new_object = malloc(sizeof(t_object));
    if (!new_object) 
    {
        perror("Allocation failed");
        exit(EXIT_FAILURE);
    }
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
            error_exit("failed to allocate\n");
    } else 
        error_exit("failed to create object \n");
}


t_scene parse(char **str) {
    char **ptr;
    int i;
    t_scene scene;
    scene.objects.head = NULL;
    i = 0;
    while (str[i]) 
    {
        ptr = ft_split(str[i], ' ');
        if (!strncmp(ptr[0], "A", ft_strlen(ptr[0])))
            parse_ambient_lightning(ptr, &scene.amb_light);
        else if (!strncmp(ptr[0], "C", ft_strlen(ptr[0])))
            parse_camera(ptr, &scene.camera);
        else if (!strncmp(ptr[0], "L", ft_strlen(ptr[0])))
            parse_light(ptr, &scene.spot_light);
        else
            parse_object(ptr, &scene.objects);
        free_split(ptr);
        i++;
    }
    return (scene);
}


t_scene check_and_fill(char **argv)
{
    t_scene scene;
    
    char *str = read_file_into_str(argv[1]);
    char **ptr = ft_split(str, '\n');
    scene = parse(ptr);
    free(str);
    int i = 0;
    while (ptr[i])
    {
        free(ptr[i]);
        i++;
    }
    free(ptr);
    return (scene);
}

int main(int ac, char **argv)
{
    t_scene scene;
    (void)ac;
    scene = check_and_fill(argv);
    print_scene(scene);
    free_scene(&scene);
    return (0);
}