/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeorges <mgeorges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:19:21 by mgeorges          #+#    #+#             */
/*   Updated: 2024/08/30 09:32:48 by mgeorges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	width_of_map(char *string)
{
	int	width;

	width = 0;
	while (string[width] != '\0')
		width++;
	if (string[width - 1] == '\n')
		width--;
	return (width);
}

char	**map_reading(t_game *game, char **av)
{
	int	i;

	i = 0;
	game->height_map = ft_height_map(game, av[1]);
	game->map = (char **)malloc(sizeof(char *) * (game->height_map + 1));
	if (game->map == NULL)
		return (NULL);
	game->fd = open(av[1], O_RDONLY);
	if (game->fd < 0)
	{
		free(game->map);
		return (NULL);
	}
	while (i < game->height_map)
	{
		game->map[i] = get_next_line(game->fd);
		if (game->map[i] == NULL)
			break ;
		i++;
	}
	game->map[i] = NULL;
	close(game->fd);
	game->width_map = width_of_map(game->map[0]);
	return (game->map);
}

int	ft_height_map(t_game *game, char *file)
{
	int		count;
	char	*line;

	count = 0;
	game->fd = open(file, O_RDONLY);
	if (game->fd < 0)
	{
		ft_printf("Error\n Error on the file");
		return (0);
	}
	while (1)
	{
		line = get_next_line(game->fd);
		if (line == NULL)
			break ;
		count++;
		free(line);
		line = NULL;
	}
	close(game->fd);
	return (count);
}
