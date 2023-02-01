#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "get_next_line.h"

void ft_memcpy(char *dest, char *src, size_t n)
{
	while (n--)
		*dest++ = *src++;
}

char *ft_realloc(char *ptr, size_t size)
{
	char *new = malloc(size);
	if (new == NULL)
		return (NULL);
	if (ptr != NULL)
	{
		ft_memcpy(new, ptr, size);
		free(ptr);
	}
	return (new);
}

char *get_next_line(int fd) {
	static char buffer[BUFF_SIZE];
	static int index = 0;
	static int bytes_read = 0;
	int i = 0;
	char *line = malloc(1);
	if (line == NULL)
		return NULL;
	line[0] = '\0';
	while (1) {
		if (index >= bytes_read) {
			bytes_read = read(fd, buffer, BUFF_SIZE);
			index = 0;
			if (bytes_read <= 0)
				return (line[0] == '\0') ? NULL : line;
		}
		if (buffer[index] == '\n') {
			line = ft_realloc(line, i + 2);
			if (line == NULL)
				return NULL;
			line[i++] = buffer[index++];
			line[i] = '\0';
			return line;
		}
		line = ft_realloc(line, i + 2);
		if (line == NULL)
			return NULL;
		line[i++] = buffer[index++];
		line[i] = '\0';
	}
}
