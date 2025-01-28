/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeorges <mgeorges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:33:00 by mgeorges          #+#    #+#             */
/*   Updated: 2024/08/28 21:09:23 by mgeorges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

int	ft_find_nl(char *s)
{
	unsigned int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] == '\0')
		return (-1);
	return (i);
}

char	*ft_create_line(char *buf_static, int index)
{
	char	*line;
	int		i;

	line = (char *)malloc((index + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buf_static[i] != '\n')
	{
		line[i] = buf_static[i];
		i++;
	}
	line[i] = '\n';
	line[i + 1] = '\0';
	return (line);
}

char	*ft_calc_line(char *buf_static)
{
	char	*line;
	int		index;

	if (ft_strlen(buf_static) <= 0)
		return (NULL);
	index = ft_find_nl(buf_static);
	if (index == -1 || index == ((int)ft_strlen(buf_static) - 1))
	{
		line = ft_strdup(buf_static);
		return (line);
	}
	line = ft_create_line(buf_static, index);
	return (line);
}

char	*ft_calc_buf(char	*buf_static)
{
	int				index;
	unsigned int	buf_len;

	if (!buf_static)
		return (NULL);
	buf_len = ft_strlen(buf_static);
	index = ft_find_nl(buf_static);
	if (index == -1 || ((buf_len - index) == 1))
	{
		free(buf_static);
		return (NULL);
	}
	buf_static = ft_substr(buf_static, (index + 1), (buf_len - index - 1));
	return (buf_static);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	int			b_read;
	static char	*buf_static;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	b_read = 1;
	while (ft_find_nl(buf_static) == -1)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read <= 0)
			break ;
		buffer[b_read] = '\0';
		buf_static = ft_strjoin(buf_static, buffer);
	}
	free(buffer);
	if (b_read == -1)
		return (NULL);
	line = ft_calc_line(buf_static);
	buf_static = ft_calc_buf(buf_static);
	return (line);
}

/*#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(void)
{
    int fd;
    char *line;

    fd = open("example.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s\n", line);
        free(line); // Libère la mémoire allouée pour la ligne
    }

    close(fd);

    return 0;
}*/
