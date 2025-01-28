/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeorges <mgeorges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:08:04 by mgeorges          #+#    #+#             */
/*   Updated: 2024/08/30 14:08:47 by mgeorges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_map_copy(char **map_copy, int height_map)
{
	int	i;

	i = 0;
	while (i < height_map)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}
