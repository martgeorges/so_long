/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeorges <mgeorges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:05:16 by mgeorges          #+#    #+#             */
/*   Updated: 2024/08/29 14:59:26 by mgeorges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	place_player(t_game *game, int height, int width)
{
	mlx_put_image_to_window(game->mlxpointer, game->winpointer, game->player,
		width * 40, height * 40);
	game->y_axis = height;
	game->x_axis = width;
}

void	place_collectable(t_game *game, int height, int width)
{
	mlx_put_image_to_window(game->mlxpointer, game->winpointer,
		game->collectibles, width * 40, height * 40);
	game->items++;
}

void	place_images_in_game(t_game *game)
{
	int	i;
	int	j;

	game->floor = mlx_xpm_file_to_image(game->mlxpointer, "assets/floor.xpm",
			&i, &j);
	game->walls = mlx_xpm_file_to_image(game->mlxpointer, "assets/wall.xpm", &i,
			&j);
	game->player = mlx_xpm_file_to_image(game->mlxpointer, "assets/player.xpm",
			&i, &j);
	game->exit = mlx_xpm_file_to_image(game->mlxpointer, "assets/exit.xpm", &i,
			&j);
	game->collectibles = mlx_xpm_file_to_image(game->mlxpointer,
			"assets/item.xpm", &i, &j);
}

static void	put_image(t_game *game, char tile, int x, int y)
{
	if (tile == '1')
		mlx_put_image_to_window(game->mlxpointer, game->winpointer, game->walls,
			x * 40, y * 40);
	else if (tile == 'C')
		place_collectable(game, y, x);
	else if (tile == 'P')
		place_player(game, y, x);
	else if (tile == 'E')
		mlx_put_image_to_window(game->mlxpointer, game->winpointer, game->exit,
			x * 40, y * 40);
	else if (tile == '0')
		mlx_put_image_to_window(game->mlxpointer, game->winpointer, game->floor,
			x * 40, y * 40);
}

void	adding_in_graphics(t_game *game)
{
	int	height;
	int	width;

	game->items = 0;
	height = 0;
	while (height < game->height_map)
	{
		width = 0;
		while (game->map[height][width])
		{
			put_image(game, game->map[height][width], width, height);
			width++;
		}
		height++;
	}
}
