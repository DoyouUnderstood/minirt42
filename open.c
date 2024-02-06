#include "parse.h"

static char *ft_strjoin_and_free(char *s1, char *s2, ssize_t n)
{
    char    *new_str;
    size_t  i;
    size_t  j;

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
    printf("file :%s\n", content);
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

// int main (int argc, char **argv)
// {
//     char *str = read_file_into_str(argv[1]);
//     char **ptr = ft_split(str, '\n');
//     ft_print_double_array(ptr);

// }