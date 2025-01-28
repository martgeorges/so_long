/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeorges <mgeorges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:57:44 by mgeorges          #+#    #+#             */
/*   Updated: 2024/08/30 13:04:30 by mgeorges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	top_bottom_walls(t_game *game)
{
	int	i;
	int	j;

	i = game->width_map;
	j = 0;
	while (j < i)
	{
		if (game->map[0][i] == '1' && game->map[game->height_map - 1][j] == '1')
			return (0);
		j++;
	}
	return (1);
}

static int	right_left_walls(t_game *game)
{
	int		height;
	int		width;
	char	left_wall;
	char	right_wall;

	height = 0;
	width = game->width_map;
	while (height < game->height_map)
	{
		left_wall = game->map[height][0];
		right_wall = game->map[height][width - 1];
		if (left_wall != '1' || right_wall != '1')
			return (0);
		height++;
	}
	return (1);
}

static void	check_walls(t_game *game)
{
	int	vertical_walls;
	int	horizontal_walls;

	vertical_walls = right_left_walls(game);
	horizontal_walls = top_bottom_walls(game);
	if (!vertical_walls || !horizontal_walls)
	{
		ft_printf("\033[0;31mError: Missing walls\n\033[0m");
		exit_game(game);
	}
}

void	check_character(t_game *game)
{
	int	height;
	int	width;

	height = 0;
	while (height < game->height_map - 1)
	{
		width = 0;
		while (width <= game->width_map)
		{
			count_checker(game, height, width);
			width++;
		}
		height++;
	}
	if (!(game->playercount == 1 && game->columncount >= 1
			&& game->exitcount == 1))
	{
		ft_printf("\033[0;31mError: something wrong\n\033[0m");
		ft_printf("\033[0;31m->P, C, 0, 1 or E\n\033[0m");
		exit_game(game);
	}
}

void	check_errors(t_game *game)
{
	if (!is_rectangular(game))
	{
		ft_printf("\033[0;31mError: Map is not rectangular\n\033[0m");
		exit_game(game);
	}
	check_walls(game);
	check_character(game);
	find_player(game);
	if (is_player_stuck(game))
	{
		ft_printf("\033[0;31mError: Player is stuck\n\033[0m");
		exit_game(game);
	}
}
