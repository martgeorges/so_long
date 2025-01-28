/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeorges <mgeorges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:15:54 by prossi            #+#    #+#             */
/*   Updated: 2024/08/30 14:10:07 by mgeorges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx/mlx.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

# define WALL '1'
# define EMPTY '0'
# define PLAYER 'P'
# define EXIT 'E'
# define COLLECTIBLE 'C'
# define VISITED 'F'

typedef struct s_point
{
	int		x;
	int		y;
}			t_point;

typedef struct s_game
{
	int		fd;
	int		height_map;
	int		width_map;
	int		playercount;
	int		columncount;
	int		exitcount;
	int		x_axis;
	int		y_axis;
	int		counter;
	int		items;
	int		player_x;
	int		player_y;

	char	**map;

	void	*floor;
	void	*walls;
	void	*player;
	void	*exit;
	void	*collectibles;
	void	*mlxpointer;
	void	*winpointer;

}			t_game;

// Main
int			exit_game(t_game *game);
void		free_images(t_game *game);
// Map
// int			map_reading(t_game *game, char **argv);
int			ft_height_map(t_game *game, char *file);
char		**map_reading(t_game *game, char **av);
// Handling Player
int			correct_move(t_game *game, int i, int j);
int			keyboard_handler(int command, t_game *game);
// Render
void		adding_in_graphics(t_game *game);
void		place_images_in_game(t_game *game);

// Error Handling
void		count_checker(t_game *game, int height, int width);
void		check_errors(t_game *game);
// Error utils
int			is_file_empty(const char *filename);
int			is_player_stuck(t_game *game);
void		find_player(t_game *game);
int			is_rectangular(t_game *game);
// Utils
int			move_up(t_game *game, int i, int j);
int			move_down(t_game *game, int i, int j);
int			move_right(t_game *game, int i, int j);
int			move_left(t_game *game, int i, int j);

// Check path
void		fill(char **tab, t_point size, int row, int col);
void		flood_fill(char **tab, t_point size, t_point begin);
void		flood_fill(char **tab, t_point size, t_point begin);
void		find_start_end_collectables(t_game *game, t_point *start,
				t_point *end, int *collectable_count);
void		check_accessibility(t_game *game);

// check path utils
void		free_map_copy_recursive(char **map_copy, int index);
char		**create_map_copy(t_game *game);
void		perform_flood_fill(char **map_copy, t_game *game, t_point start);
void		verify_accessibility(char **map_copy, t_game *game,
				int collectable_count, t_point end);
void		free_map_copy(char **map_copy, int height_map);
int			count_chars(const char *str, char ch);

#endif
