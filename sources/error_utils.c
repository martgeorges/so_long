/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeorges <mgeorges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:43:48 by mgeorges          #+#    #+#             */
/*   Updated: 2024/08/30 09:46:59 by mgeorges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	is_file_empty(const char *filename)
{
	int		fd;
	char	buffer[1];
	int		bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	bytes_read = read(fd, buffer, 1);
	if (bytes_read == -1)
	{
		perror("Error reading file");
		close(fd);
		return (1);
	}
	close(fd);
	if (bytes_read == 0)
	{
		write(2, "\033[0;31mError: Empty map!\n\033[0m", 30);
		return (1);
	}
	return (0);
}

int	is_player_stuck(t_game *game)
{
	int	x;
	int	y;

	x = game->player_x;
	y = game->player_y;
	if ((y > 0 && game->map[y - 1][x] != WALL) || (y < game->height_map - 1
			&& game->map[y + 1][x] != WALL) || (x > 0 && game->map[y][x
			- 1] != WALL) || (x < game->width_map - 1 && game->map[y][x
			+ 1] != WALL))
		return (0);
	return (1);
}

void	find_player(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->height_map)
	{
		x = 0;
		while (x < game->width_map)
		{
			if (game->map[y][x] == PLAYER)
			{
				game->player_x = x;
				game->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

int	is_rectangular(t_game *game)
{
	int	i;
	int	expected_width;

	i = 0;
	expected_width = ft_strlen(game->map[0]);
	while (i < game->height_map)
	{
		if (ft_strlen(game->map[i]) != (size_t)expected_width)
			return (0);
		i++;
	}
	return (1);
}
