/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeorges <mgeorges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:12:01 by mgeorges          #+#    #+#             */
/*   Updated: 2024/08/30 14:29:42 by mgeorges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	*ft_memset(void *b, int c, size_t length)
{
	unsigned char	*p;

	p = (unsigned char *)b;
	while (length--)
		*p++ = (unsigned char)c;
	return (b);
}

void	free_images(t_game *game)
{
	if (game->floor)
		mlx_destroy_image(game->mlxpointer, game->floor);
	if (game->walls)
		mlx_destroy_image(game->mlxpointer, game->walls);
	if (game->player)
		mlx_destroy_image(game->mlxpointer, game->player);
	if (game->exit)
		mlx_destroy_image(game->mlxpointer, game->exit);
	if (game->collectibles)
		mlx_destroy_image(game->mlxpointer, game->collectibles);
}

int	exit_game(t_game *game)
{
	int	line;

	line = 0;
	if (game->winpointer)
		mlx_destroy_window(game->mlxpointer, game->winpointer);
	if (game->winpointer)
	{
		free_images(game);
		mlx_destroy_display(game->mlxpointer);
		free(game->mlxpointer);
	}
	while (line < game->height_map)
		free(game->map[line++]);
	free(game->map);
	exit(0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		ft_printf("\033[0;31mError: ./so_long [mapx.ber]\n\033[0m");
		return (0);
	}
	ft_memset(&game, 0, sizeof(t_game));
	if (is_file_empty(av[1]))
		exit(1);
	map_reading(&game, av);
	check_errors(&game);
	check_accessibility(&game);
	game.mlxpointer = mlx_init();
	game.winpointer = mlx_new_window(game.mlxpointer, (game.width_map * 40),
			(game.height_map * 40), "so_long");
	place_images_in_game(&game);
	adding_in_graphics(&game);
	mlx_hook(game.winpointer, 02, (1L << 0), keyboard_handler, &game);
	mlx_hook(game.winpointer, 17, (1L << 17), exit_game, &game);
	mlx_loop(game.mlxpointer);
	exit_game(&game);
}
