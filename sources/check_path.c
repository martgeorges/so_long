/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeorges <mgeorges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:06:09 by mgeorges          #+#    #+#             */
/*   Updated: 2024/08/30 13:47:15 by mgeorges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	fill(char **tab, t_point size, int row, int col)
{
	if (row < 0 || col < 0 || row >= size.y || col >= size.x)
		return ;
	if (tab[row][col] == 'F' || tab[row][col] == '1' || tab[row][col] == 'c'
		|| tab[row][col] == 'p' || tab[row][col] == 'e')
		return ;
	if (tab[row][col] == 'C')
		tab[row][col] = 'c';
	else if (tab[row][col] == 'P')
		tab[row][col] = 'p';
	else if (tab[row][col] == 'E')
		tab[row][col] = 'e';
	else
		tab[row][col] = 'F';
	fill(tab, size, row - 1, col);
	fill(tab, size, row + 1, col);
	fill(tab, size, row, col - 1);
	fill(tab, size, row, col + 1);
}

void	flood_fill(char **tab, t_point size, t_point begin)
{
	fill(tab, size, begin.y, begin.x);
}

void	find_start_end_collectables(t_game *game, t_point *start, t_point *end,
		int *collectable_count)
{
	int		i;
	int		j;
	char	cell;

	i = 0;
	*start = (t_point){-1, -1};
	*end = (t_point){-1, -1};
	*collectable_count = 0;
	while (i < game->height_map)
	{
		j = 0;
		while (j < game->width_map)
		{
			cell = game->map[i][j];
			if (cell == 'P')
				*start = (t_point){j, i};
			else if (cell == 'E')
				*end = (t_point){j, i};
			else if (cell == 'C')
				(*collectable_count)++;
			j++;
		}
		i++;
	}
}

void	check_accessibility(t_game *game)
{
	int		collectable_count;
	char	**map_copy;
	t_point	start;
	t_point	end;

	find_start_end_collectables(game, &start, &end, &collectable_count);
	map_copy = create_map_copy(game);
	perform_flood_fill(map_copy, game, start);
	verify_accessibility(map_copy, game, collectable_count, end);
	free_map_copy(map_copy, game->height_map);
}
