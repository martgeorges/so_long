/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeorges <mgeorges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:27:46 by mgeorges          #+#    #+#             */
/*   Updated: 2024/08/30 14:11:03 by mgeorges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_map_copy_recursive(char **map_copy, int index)
{
	if (index < 0)
		return ;
	free(map_copy[index]);
	free_map_copy_recursive(map_copy, index - 1);
}

char	**create_map_copy(t_game *game)
{
	char	**map_copy;
	int		i;

	map_copy = malloc(game->height_map * sizeof(char *));
	if (!map_copy)
	{
		perror("Failed to allocate memory");
		exit(1);
	}
	i = 0;
	while (i < game->height_map)
	{
		map_copy[i] = strdup(game->map[i]);
		if (!map_copy[i])
		{
			perror("Failed to allocate memory");
			free_map_copy_recursive(map_copy, i - 1);
			free(map_copy);
			exit(1);
		}
		i++;
	}
	return (map_copy);
}

void	perform_flood_fill(char **map_copy, t_game *game, t_point start)
{
	flood_fill(map_copy, (t_point){game->width_map, game->height_map}, start);
}

void	verify_accessibility(char **map_copy, t_game *game,
		int collectable_count, t_point end)
{
	int	collected_count;
	int	i;

	collected_count = 0;
	i = 0;
	while (i < game->height_map)
	{
		collected_count += count_chars(map_copy[i], 'c');
		i++;
	}
	if (collected_count != collectable_count || map_copy[end.y][end.x] != 'e')
	{
		ft_printf("\033[0;31mError: Invalid path\n\033[0m");
		free_map_copy(map_copy, game->height_map);
		exit_game(game);
	}
}

int	count_chars(const char *str, char ch)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == ch)
			count++;
		str++;
	}
	return (count);
}
