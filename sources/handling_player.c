/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeorges <mgeorges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:49:33 by mgeorges          #+#    #+#             */
/*   Updated: 2024/08/29 15:35:22 by mgeorges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	correct_move(t_game *game, int i, int j)
{
	if (game->map[j][i] == 'E')
	{
		if (game->items != 0)
			return (0);
		ft_printf("\033[0;32m\nYou Have Won, Congrats!\n\033[0m");
		ft_printf("\033[0;32min %d moves !\n\033[0m", game->counter);
		exit_game(game);
	}
	if (game->map[j][i] == '0')
	{
		game->map[j][i] = 'P';
		game->x_axis = i;
		game->y_axis = j;
		game->counter++;
	}
	if (game->map[j][i] == 'C')
	{
		game->map[j][i] = 'P';
		game->x_axis = i;
		game->y_axis = j;
		game->items--;
		game->counter++;
	}
	return (1);
}

static int	up_down(t_game *game, int movement)
{
	int	i;
	int	j;
	int	result;

	i = game->x_axis;
	j = game->y_axis;
	if (movement == 13)
		result = move_up(game, i, j);
	else if (movement == 1)
		result = move_down(game, i, j);
	else
		return (0);
	if (result)
	{
		ft_printf("\033[1m\033[93mSteps Taken:\033[0m\n");
		ft_printf("\033[0;32m->%d\n\033[0m", game->counter);
		ft_printf("\033[1m\033[38;5;214mItems left:\033[0m\n");
		ft_printf("\033[0;31m->%d\n\033[0m", game->items);
	}
	return (result);
}

static int	right_left(t_game *game, int movement)
{
	int	i;
	int	j;
	int	result;

	i = game->x_axis;
	j = game->y_axis;
	if (movement == 0)
		result = move_left(game, i, j);
	else if (movement == 2)
		result = move_right(game, i, j);
	else
		return (0);
	if (result)
	{
		ft_printf("\033[1m\033[93mSteps Taken:\033[0m\n");
		ft_printf("\033[0;32m->%d\n\033[0m", game->counter);
		ft_printf("\033[1m\033[38;5;214mItems left:\033[0m\n");
		ft_printf("\033[0;31m->%d\n\033[0m", game->items);
	}
	return (result);
}

int	keyboard_handler(int command, t_game *game)
{
	int	works;

	works = 0;
	if (command == 65307)
		exit_game(game);
	if (command == 122 || command == 65362)
		works = up_down(game, 13);
	if (command == 115 || command == 65364)
		works = up_down(game, 1);
	if (command == 113 || command == 65361)
		works = right_left(game, 0);
	if (command == 100 || command == 65363)
		works = right_left(game, 2);
	if (works)
		adding_in_graphics(game);
	return (1);
}
