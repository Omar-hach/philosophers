
#include <unistd.h>
#include <stdlib.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

#include <fcntl.h>
#include <string.h>

void *ft_calloc(size_t count, size_t size)
{
    char *p;
    int i = -1;
    void *mem;

    mem = malloc(count * size);
    if(!mem)
        return(NULL);
    p = (char *)mem;
    while(++i < count * size)
        p[i] = 0;
    return(mem);
}



char	*get_next_line(int fd)
{
    char *buff;
    char *line;
    char *rest;
    int i = -1;
    int size = 0;

    buff = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
    size += read(fd, buff, BUFFER_SIZE);
    /*while(buff != NULL)
    {
        while(buff[i++] == '\n')
        if(strlen(buff) != i + 1)
            break ;
        size += read(fd, buff, BUFFER_SIZE);
    }*/
    return(buff);
}

int	main()
{
    int fd = open("text.txt",O_RDONLY);
    char *word = get_next_line(fd);
    printf("%s",word);
    free(word);
}