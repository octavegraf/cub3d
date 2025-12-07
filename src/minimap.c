/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan-re <rchan-re@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:57:29 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/07 18:32:12 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef BONUS
static void	fill_minimap(t_game *game, t_quadri *quadri)
{
	int	x;
	int	y;

	x = quadri->x_start;
	while (x <= quadri->x_end)
	{
		y = quadri->y_start;
		while (y <= quadri->y_end)
		{
			img_fill_pixel(game->mlx.frame, y, x, quadri->color);
			y++;
		}
		x++;
	}
}

static int	get_y_quadri(t_game *game, int j, t_quadri *quadri)
{
	int		y_player_index;
	float	y_player_real;

	y_player_index = RADIUS_MAP;
	y_player_real = RADIUS_MAP + (game->player.pos_y - ((int)(game->player.pos_y)));
	// above, complete square
	if (j < y_player_index && y_player_real * game->minimap_scale_screen_map - game->minimap_radius_screen <= j)
	{
		quadri->y_start = j * game->minimap_scale_screen_map - (y_player_real * game->minimap_scale_screen_map - game->minimap_radius_screen);
		quadri->y_end = quadri->y_start + 1 * game->minimap_scale_screen_map;
		return (1);
	}
	// above, partial square
	else if (j < y_player_index && y_player_real * game->minimap_scale_screen_map - game->minimap_radius_screen < (j + 1) * game->minimap_scale_screen_map)
	{
		quadri->y_start = 0;
		quadri->y_end = (j + 1) * game->minimap_scale_screen_map - (y_player_real * game->minimap_scale_screen_map - game->minimap_radius_screen);
		return (1);
	}
	// same location, partial square
	else if (j == y_player_index && y_player_real * game->minimap_scale_screen_map - game->minimap_radius_screen > j * game->minimap_scale_screen_map)
	{
		quadri->y_start = 0;
		quadri->y_end = 2 * game->minimap_radius_screen;
		return (1);
	}
	// same location, complete square
	else if (j == y_player_index)
	{
		quadri->y_start = j * game->minimap_scale_screen_map - (y_player_real * game->minimap_scale_screen_map - game->minimap_radius_screen);
		quadri->y_end = quadri->y_start + 1 * game->minimap_scale_screen_map;
		return (1);
	}
	// under, complete square
	else if (j > y_player_index && y_player_real * game->minimap_scale_screen_map + game->minimap_radius_screen >= (j + 1) * game->minimap_scale_screen_map)
	{
		quadri->y_start = j * game->minimap_scale_screen_map - (y_player_real * game->minimap_scale_screen_map - game->minimap_radius_screen);
		quadri->y_end = quadri->y_start + 1 * game->minimap_scale_screen_map;
		return (1);
	}
	// under, partial square
	else if (j > y_player_index && y_player_real * game->minimap_scale_screen_map + game->minimap_radius_screen > j * game->minimap_scale_screen_map)
	{
		quadri->y_start = j * game->minimap_scale_screen_map - (y_player_real * game->minimap_scale_screen_map - game->minimap_radius_screen);
		// quadri->y_end = y_player_real * game->minimap_scale_screen_map + game->minimap_radius_screen;
		quadri->y_end = 2 * game->minimap_radius_screen;
		return (1);
	}
	return (0);
}

static int	get_x_quadri(t_game *game, int i, t_quadri *quadri)
{
	int		x_player_index;
	float	x_player_real;

	//x_player = RADIUS_MAP + game->player.pos_x - ((int)(game->player.pos_x));
	x_player_index = RADIUS_MAP;
	x_player_real = RADIUS_MAP + (game->player.pos_x - ((int)(game->player.pos_x)));
	// left side, complete square
	if (i < x_player_index && x_player_real * game->minimap_scale_screen_map - game->minimap_radius_screen <= i * game->minimap_scale_screen_map)
		return (quadri->x_start = i * game->minimap_scale_screen_map - (x_player_real * game->minimap_scale_screen_map - game->minimap_radius_screen), quadri->x_end = quadri->x_start + 1 * game->minimap_scale_screen_map, 1);
	// left side, partial square
	else if (i < x_player_index && x_player_real * game->minimap_scale_screen_map - game->minimap_radius_screen < (i + 1) * game->minimap_scale_screen_map)
		return (quadri->x_start = 0, quadri->x_end = (i + 1) * game->minimap_scale_screen_map - (x_player_real * game->minimap_scale_screen_map - game->minimap_radius_screen), 1);
	// same location as player, partial square
	else if (i == x_player_index && x_player_real * game->minimap_scale_screen_map - game->minimap_radius_screen > i * game->minimap_scale_screen_map)
		return (quadri->x_start = 0, quadri->x_end = x_player_real * game->minimap_scale_screen_map + game->minimap_radius_screen, 1);
	// same location as player, complete square
	else if (i == x_player_index)
		return (quadri->x_start = i * game->minimap_scale_screen_map - (x_player_real * game->minimap_scale_screen_map - game->minimap_radius_screen), quadri->x_end = quadri->x_start + 1 * game->minimap_scale_screen_map, 1);
	// right side, complete square
	else if (i > x_player_index && x_player_real * game->minimap_scale_screen_map + game->minimap_radius_screen >= (i + 1) * game->minimap_scale_screen_map)
		return (quadri->x_start = i * game->minimap_scale_screen_map - (x_player_real * game->minimap_scale_screen_map - game->minimap_radius_screen), quadri->x_end = quadri->x_start + 1 * game->minimap_scale_screen_map, 1);
	// right side, partial square
	else if (i > x_player_index && x_player_real * game->minimap_scale_screen_map + game->minimap_radius_screen > i * game->minimap_scale_screen_map)
		return (quadri->x_start = i * game->minimap_scale_screen_map - (x_player_real * game->minimap_scale_screen_map - game->minimap_radius_screen), quadri->x_end = 2 * game->minimap_radius_screen, 1);
	return (0);
}

static void draw_quadri_minimap(t_game *game, char minimap[(RADIUS_MAP * 2) + 1][(RADIUS_MAP * 2) + 1])
{
	int			i;
	int			j;
	t_quadri	quadri;

	i = 0;
	j = 0;
	while (i < (RADIUS_MAP * 2) + 1)
	{
		if (get_x_quadri(game, i, &quadri))
		{
			j = 0;
			while (j < (RADIUS_MAP * 2) + 1)
			{
				if (get_y_quadri(game, j, &quadri))
				{
					quadri.color = BLACK;
					if (ft_strchr("0EWNS", minimap[i][j]) != NULL)
						quadri.color = WHITE;
					fill_minimap(game, &quadri);	
				}
				j++;
			}
		}
		i++;
	}
}

static unsigned int	tab_size(char	**tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

static void	get_minimap(t_game *game, char minimap[(RADIUS_MAP * 2) + 1][(RADIUS_MAP * 2) + 1])
{
	int	i;
	int	j;
	int	map_size_x;
	int	map_size_y;

	i = 0;
	map_size_x = tab_size(game->scene.map);
	while (i < (RADIUS_MAP * 2) + 1)
	{
		if (i + ((int)(game->player.pos_x)) - RADIUS_MAP >= 0 &&   i + ((int)(game->player.pos_x)) - RADIUS_MAP < map_size_x)
			map_size_y = ft_strlen(game->scene.map[i + ((int)(game->player.pos_x)) - RADIUS_MAP]);
		else
			map_size_y = -1;
		j = 0;
		while (j < (RADIUS_MAP * 2) + 1)
		{
			if (i + ((int)(game->player.pos_x)) - RADIUS_MAP < 0 || i + ((int)(game->player.pos_x)) - RADIUS_MAP >= map_size_x
				|| j + ((int)(game->player.pos_y)) - RADIUS_MAP < 0 || j + ((int)(game->player.pos_y)) - RADIUS_MAP >= map_size_y)
				minimap[i][j] = '1';
			else if (game->scene.map[i + ((int)(game->player.pos_x)) - RADIUS_MAP][j + ((int)(game->player.pos_y)) - RADIUS_MAP] != '0')
				minimap[i][j] = '1';
			else
				minimap[i][j] = '0';
			j++;
		}
		i++;
	}
}

/*
static void	print_minimap(char minimap[(RADIUS_MAP * 2) + 1][(RADIUS_MAP * 2) + 1])
{
	int	i;
	int	j;

	i = 0;
	while (i < (RADIUS_MAP * 2) + 1)
	{
		j = 0;
		while (j < (RADIUS_MAP * 2) + 1)
		{
			ft_printf("[%c]", minimap[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}*/

static void	draw_player_fov_minimap(t_game *game)
{
	int	ray_pos_x;
	int	ray_pos_y;
	int	i;

	i = 0;
	while (i < MINIMAP_NB_PIXELS_FOV)
	{
		// get partial ray_dir
		ray_pos_x = (game->player.dir_x - game->player.plane_x) * game->minimap_scale_screen_map * i * MINIMAP_FOV_STEP;
		ray_pos_y = (game->player.dir_y - game->player.plane_y) * game->minimap_scale_screen_map * i * MINIMAP_FOV_STEP;
		img_fill_pixel(game->mlx.frame, RADIUS_MAP * game->minimap_scale_screen_map + ray_pos_y, RADIUS_MAP * game->minimap_scale_screen_map + ray_pos_x, RED);
		ray_pos_x = (game->player.dir_x + game->player.plane_x) * game->minimap_scale_screen_map * i * MINIMAP_FOV_STEP;
		ray_pos_y = (game->player.dir_y + game->player.plane_y) * game->minimap_scale_screen_map * i * MINIMAP_FOV_STEP;
		img_fill_pixel(game->mlx.frame, RADIUS_MAP * game->minimap_scale_screen_map + ray_pos_y, RADIUS_MAP * game->minimap_scale_screen_map + ray_pos_x, RED);
		i++;
	}



}

int	display_minimap(t_game *game)
{
	char		minimap[(RADIUS_MAP * 2) + 1][(RADIUS_MAP * 2) + 1];
	t_quadri	quadri;

	get_minimap(game, minimap);
	//print_minimap(minimap);
	draw_quadri_minimap(game, minimap);
	quadri.x_start = RADIUS_MAP * game->minimap_scale_screen_map - SIZE_PLAYER;
	quadri.x_end = RADIUS_MAP * game->minimap_scale_screen_map + SIZE_PLAYER;
	quadri.y_start = RADIUS_MAP * game->minimap_scale_screen_map - SIZE_PLAYER;
	quadri.y_end = RADIUS_MAP * game->minimap_scale_screen_map + SIZE_PLAYER;
	quadri.color = RED;
	fill_minimap(game, &quadri);
	// draw outline minimap
	// draw player FOV
	draw_player_fov_minimap(game);
	return (1);
}
#endif
