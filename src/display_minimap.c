/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan-re <rchan-re@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:43:24 by rchan-re          #+#    #+#             */
/*   Updated: 2025/11/11 17:43:24 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	minimap_get_dimensions(t_game *game, int *nb_pixels)
{
	int		j;
	int		dim_screen;
	int		width;
	int		height;

	width = 0;
	height = 0;
	while (game->scene.map[height] != NULL)
	{
		j = 0;
		while (game->scene.map[height][j] != '\0')
			j++;
		if (j > width)
			width = j;
		height += 1;
	}
	dim_screen = MINIMAP_RATIO * HEIGHT;
	*nb_pixels = dim_screen / height;
	if (width >= height)
	{
		dim_screen = MINIMAP_RATIO * WIDTH;
		*nb_pixels = dim_screen / width;
	}
}

static void	minimap_fill_pixel(t_game *game, int nb_pixels, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < nb_pixels)
	{
		j = 0;
		while (j < nb_pixels)
		{
			if (game->scene.map[x][y] == '0')
				img_fill_pixel(game->mlx.frame, nb_pixels * y + i,
					nb_pixels * x + j, WHITE);
			else
				img_fill_pixel(game->mlx.frame, nb_pixels * y + i,
					nb_pixels * x + j, BLACK);
			j++;
		}
		i++;
	}
}

static void	minimap_fill(t_game *game, int nb_pixels)
{
	int		i;
	int		j;

	i = 0;
	while (game->scene.map[i] != NULL)
	{
		j = 0;
		while (game->scene.map[i][j] != '\0')
		{
			minimap_fill_pixel(game, nb_pixels, i, j);
			j++;
		}
		i++;
	}
}

static void	minimap_update_player_position(t_game *game, int nb_pixels)
{
	int	x;
	int	y;
	int	i;
	int	j;

	x = game->player.pos_x;
	y = game->player.pos_y;
	i = 0;
	while (i < nb_pixels)
	{
		j = 0;
		while (j < nb_pixels)
		{
			img_fill_pixel(game->mlx.frame, nb_pixels * y + i,
				nb_pixels * x + j, RED);
			j++;
		}
		i++;
	}
}

int	display_minimap(t_game *game)
{
	static int	nb_pixels = 0;
	static int	n = 0;

	if (n == 0)
	{
		minimap_get_dimensions(game, &nb_pixels);
		n++;
	}
	if (nb_pixels == 0)
		return (0);
	minimap_fill(game, nb_pixels);
	minimap_update_player_position(game, nb_pixels);
	return (1);
}
