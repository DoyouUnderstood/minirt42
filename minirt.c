#include "parse.h"

static char *ft_strjoin_and_free(char *s1, char *s2, ssize_t n)
{
    char    *new_str;
    ssize_t  i;

    if (!s1 || !s2)
        return (NULL);
    new_str = (char *)malloc(sizeof(*new_str) * (n + 1));
    if (!new_str)
        return (NULL);
    i = -1;
    while (++i < n && s2[i] != '\0')
        new_str[i] = s2[i];
    new_str[i] = '\0';
    free(s1);
    return (new_str);
}

char    *read_file_into_str(const char *file_path)
{
    int     fd;
    ssize_t bytes_read;
    char    buffer[1024];
    char    *content;
    char    *temp;

    fd = open(file_path, O_RDONLY);
    if (fd == -1)
        return (NULL);
    content = malloc(1);
    if (!content)
        return (NULL);
    content[0] = '\0';
    while ((bytes_read = read(fd, buffer, 1024)) > 0)
    {
        temp = ft_strjoin_and_free(content, buffer, bytes_read);
        if (!temp)
        {
            free(content);
            close(fd);
            return (NULL);
        }
        content = temp;
    }
    if (bytes_read == -1)
    {
        free(content);
        close(fd);
        return (NULL);
    }
    close(fd);
    return (content);
}

void    ft_print_double_array(char **arr)
{
   int i;

    if (!arr)
        return;
    i = 0;
    while (arr[i] != NULL) // La fin du tableau est marquée par un pointeur NULL
    {
        printf("%s\n", arr[i]);
        i++;
    }
}

//separer la fonction est gerer les erreurs de retour.

void parse(char **str)
{
    char **ptr;
    int i;
    t_camera camera;
    t_light light;
    t_sphere sphere;
    t_plane plane;
    t_amb_light am_light;
    t_cyl cyl;

    i = 0;
    ptr = NULL;
    while (str[i])
    {
        ptr = ft_split(str[i], ' ');
        if (!strncmp(ptr[0], "A", strlen(ptr[0])))
            parse_ambient_lightning(ptr, &am_light);
        else if (!strncmp(ptr[0], "C", strlen(ptr[0])))
            parse_camera(ptr, &camera);
        else if (!strncmp(ptr[0], "L", strlen(ptr[0])))
            parse_light(ptr, &light);
        else if (!strncmp(ptr[0], "pl", strlen(ptr[0])))
            parse_plane(ptr, &plane);
        else if (!strncmp(ptr[0], "sp", strlen(ptr[0])))
            parse_sphere(ptr, &sphere);
        else if (!strncmp(ptr[0], "cy", strlen(ptr[0])))
            parse_cylinder(ptr, &cyl);
        i++;
    }
    print_amb_light(am_light);
    print_camera(camera);
    print_light(light);
    print_plane(plane);
    print_sphere(sphere);
    print_cyl(cyl);
}
int main(int ac, char **argv)
{
    (void)ac;
    char *str = read_file_into_str(argv[1]);
    char **ptr = ft_split(str, '\n');
    // ft_print_double_array(ptr);
    // printf("===================\n");
    parse(ptr);
    // t_camera camera;
    // t_light light;
    // t_sphere sphere;
    // t_plane plane;
    // t_cyl cyl;
    
    // char *line = "C -50.0,0aaaa,20     0,0,1   70";
    // char *line_C = "L -40.0,50.0,0.0 0.6 10,0,255";
    // char *line_sp = "sp 199999,0.0,20.6 12.6 10,0,255";
    // char *line_pl = "pl 0.0,0.0,-1088888.0 0.0,1.....0,0.0 0,0,225";
    // char *line_cy = "cy 50.0,0.0,20.6 0.0,0.0,1.0 1fghj4.2 21.42 10,0,255";

    // int res_cy = parse_cylinder(line_cy, &cyl);
    // int res_sp = parse_sphere(line_sp, &sphere);
    // int res_C = parse_camera(line, &camera);
    // int res_L = parse_light(line_C, &light);
    // int res_pl = parse_plane(line_pl, &plane);
    // print_camera(&camera);
    // print_cylinder(&cyl);
    // printf("%d\n", res_L);
    // printf("%d\n", res_C);
    // printf("%d\n", res_sp);
    // printf("%d\n", res_pl);
    // printf("%d\n", res_cy);

    // print_plane(&plane);
    // print_sphere(&sphere);
    // print_light(&light);
}