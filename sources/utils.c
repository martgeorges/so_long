/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeorges <mgeorges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:46:46 by mgeorges          #+#    #+#             */
/*   Updated: 2024/08/29 14:59:20 by mgeorges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	count_checker(t_game *game, int height, int width)
{
	if (game->map[height][width] != '1' && game->map[height][width] != '0'
		&& game->map[height][width] != 'P' && game->map[height][width] != 'E'
		&& game->map[height][width] != 'C' && game->map[height][width] != '\n')
	{
		ft_printf("\033[0;31mError!->[%c]\n\033[0m", game->map[height][width]);
		exit_game(game);
	}
	if (game->map[height][width] == 'C')
		game->columncount++;
	if (game->map[height][width] == 'P')
		game->playercount++;
	if (game->map[height][width] == 'E')
		game->exitcount++;
}

int	move_up(t_game *game, int i, int j)
{
	int	k;

	j--;
	if (game->map[j][i] == '1')
		return (0);
	k = correct_move(game, i, j);
	if (!k)
		return (0);
	game->map[j + 1][i] = '0';
	return (1);
}

int	move_down(t_game *game, int i, int j)
{
	int	k;

	j++;
	if (game->map[j][i] == '1')
		return (0);
	k = correct_move(game, i, j);
	if (!k)
		return (0);
	game->map[j - 1][i] = '0';
	return (1);
}

int	move_right(t_game *game, int i, int j)
{
	int	k;

	i++;
	if (game->map[j][i] == '1')
		return (0);
	k = correct_move(game, i, j);
	if (!k)
		return (0);
	game->map[j][i - 1] = '0';
	return (1);
}

int	move_left(t_game *game, int i, int j)
{
	int	k;

	i--;
	if (game->map[j][i] == '1')
		return (0);
	k = correct_move(game, i, j);
	if (!k)
		return (0);
	game->map[j][i + 1] = '0';
	return (1);
}
