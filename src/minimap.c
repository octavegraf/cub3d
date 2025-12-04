/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan-re <rchan-re@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:57:29 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/04 17:33:52 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef BONUS
static void	fill_minimap(t_game *game, t_quadri *quadri)
{
	int	i;
	int	j;

	ft_printf("quadri: %d %d, %d %d\n", quadri->x_start, quadri->x_end, quadri->y_start, quadri->y_end);
	i = quadri->x_start;
	while (i <= quadri->x_end)
	{
		j = quadri->y_start;
		while (j <= quadri->y_end)
		{
			img_fill_pixel(game->mlx.frame, i, j, quadri->color);
			j++;
		}
		i++;
	}
}

static int	get_y_quadri(t_game *game, int j, int radius_map, t_quadri *quadri)
{
	int	y_player;

	y_player = game->player.pos_y;
	// above, complete square
	if (j < y_player && game->player.pos_y * SCALE_SCREEN_MAP - radius_map < j)
	{
		printf("yes1 : %d %d, %f %f\n", j, radius_map, game->player.pos_x, game->player.pos_y);
		printf("rad %d\n", radius_map);
		quadri->y_start = j * SCALE_SCREEN_MAP - (game->player.pos_y * SCALE_SCREEN_MAP - radius_map);
		quadri->y_end = quadri->y_start + 1 * SCALE_SCREEN_MAP;
		return (1);
	}
	// above, partial square
	else if (j < y_player && game->player.pos_y * SCALE_SCREEN_MAP - radius_map < (j + 1) * SCALE_SCREEN_MAP)
	{
		ft_printf("yes2\n");
		quadri->y_start = 0;
		quadri->y_end = j * SCALE_SCREEN_MAP - (game->player.pos_y * SCALE_SCREEN_MAP - radius_map);
		return (1);
	}
	// same location, partial square
	else if (j == y_player && game->player.pos_y * SCALE_SCREEN_MAP - radius_map > j * SCALE_SCREEN_MAP)
	{
		quadri->y_start = 0;
		quadri->y_end = 2 * radius_map;
		return (1);
	}
	// same location, complete square
	else if (j == y_player)
	{
		quadri->y_start = j * SCALE_SCREEN_MAP - (game->player.pos_y * SCALE_SCREEN_MAP - radius_map);
		quadri->y_end = quadri->y_start + 1 * SCALE_SCREEN_MAP;
		return (1);
	}
	// under, complete square
	else if (j > y_player && game->player.pos_y * SCALE_SCREEN_MAP + radius_map > (j + 1) * SCALE_SCREEN_MAP)
	{
		quadri->y_start = j * SCALE_SCREEN_MAP - (game->player.pos_y * SCALE_SCREEN_MAP - radius_map);
		quadri->y_end = quadri->y_start + 1 * SCALE_SCREEN_MAP;
		return (1);
	}
	// under, partial square
	else if (j > y_player && game->player.pos_y * SCALE_SCREEN_MAP + radius_map > j * SCALE_SCREEN_MAP)
	{
		quadri->y_start = j * SCALE_SCREEN_MAP - (game->player.pos_y * SCALE_SCREEN_MAP - radius_map);
		quadri->y_end = game->player.pos_y * SCALE_SCREEN_MAP + radius_map;
		return (1);
	}
	return (0);
}

static int	get_x_quadri(t_game *game, int i, int radius_map, t_quadri *quadri)
{
	int	x_player;

	x_player = game->player.pos_x;
	// left side, complete square
	if (i < x_player && game->player.pos_x * SCALE_SCREEN_MAP - radius_map < i * SCALE_SCREEN_MAP)
		return (quadri->x_start = i * SCALE_SCREEN_MAP - (game->player.pos_x * SCALE_SCREEN_MAP - radius_map), quadri->x_end = quadri->x_start + 1 * SCALE_SCREEN_MAP, 1);
	// left side, partial square
	else if (i < x_player && game->player.pos_x * SCALE_SCREEN_MAP - radius_map < (i + 1) * SCALE_SCREEN_MAP)
		return (quadri->x_start = 0, quadri->x_end = (i + 1) * SCALE_SCREEN_MAP - (game->player.pos_x * SCALE_SCREEN_MAP - radius_map), 1);
	// same location as player, partial square
	else if (i == x_player && game->player.pos_x * SCALE_SCREEN_MAP - radius_map > i * SCALE_SCREEN_MAP)
		return (quadri->x_start = 0, quadri->x_end = game->player.pos_x * SCALE_SCREEN_MAP + radius_map, 1);
	// same location as player, complete square
	else if (i == x_player)
		return (quadri->x_start = i * SCALE_SCREEN_MAP - (game->player.pos_x * SCALE_SCREEN_MAP - radius_map), quadri->x_end = quadri->x_start + 1 * SCALE_SCREEN_MAP, 1);
	// right side, complete square
	else if (i > x_player && game->player.pos_x * SCALE_SCREEN_MAP + radius_map > (i + 1) * SCALE_SCREEN_MAP)
		return (quadri->x_start = i * SCALE_SCREEN_MAP - (game->player.pos_x * SCALE_SCREEN_MAP - radius_map), quadri->x_end = quadri->x_start + 1 * SCALE_SCREEN_MAP, 1);
	// right side, partial square
	else if (i > x_player && game->player.pos_x * SCALE_SCREEN_MAP + radius_map > i * SCALE_SCREEN_MAP)
		return (quadri->x_start = i * SCALE_SCREEN_MAP - (game->player.pos_x * SCALE_SCREEN_MAP - radius_map), quadri->x_end = quadri->x_start + radius_map, 1);
	return (0);
}

static void draw_quadri_minimap(t_game *game, float radius_screen)
{
	int			i;
	int			j;
	t_quadri	quadri;

	i = 0;
	j = 0;
	while (game->scene.map[i] != NULL)
	{
		if (get_y_quadri(game, i, radius_screen, &quadri))
		{
			j = 0;
			while (game->scene.map[i][j] != '\0')
			{
				if (get_x_quadri(game, j, radius_screen, &quadri))
				{
					quadri.color = BLACK;
					if (ft_strchr("0EWNS", game->scene.map[i][j]) != NULL)
						quadri.color = WHITE;
					ft_printf("%d %d\n", i, j);
					fill_minimap(game, &quadri);	
					//while (1);
				}
				j++;
			}
		}
		i++;
	}
}

int	display_minimap(t_game *game)
{
/*	float	radius_screen;
	float	radius_map;

	// get radius
	if (HEIGHT > WIDTH)
		radius_screen = MINIMAP_RATIO * HEIGHT;
	else
		radius_screen = MINIMAP_RATIO * WIDTH;
	// convert radius in map coordinates
	radius_map = radius_screen * RATIO_MAP_SCREEN;
	// fill minimap from top to bottom, left to right
	fill_minimap(game);
	// draw FOV
*/
/*	t_quadri	quadri;

	quadri.x_start = 0;
	quadri.x_end = RADIUS_PIXELS;
	quadri.y_start = 0;
	quadri.y_end = RADIUS_PIXELS;
	quadri.color = RED;
	fill_minimap(game, &quadri);*/
	t_quadri	quadri;

	draw_quadri_minimap(game, RADIUS_MAP * SCALE_SCREEN_MAP);
	quadri.x_start = game->player.pos_x * SCALE_SCREEN_MAP;
	quadri.x_end = game->player.pos_x * SCALE_SCREEN_MAP + SCALE_SCREEN_MAP;
	quadri.y_start = game->player.pos_y * SCALE_SCREEN_MAP;
	quadri.y_end = game->player.pos_y * SCALE_SCREEN_MAP + SCALE_SCREEN_MAP;
	quadri.color = RED;
	fill_minimap(game, &quadri);
	return (1);
}
#endif
