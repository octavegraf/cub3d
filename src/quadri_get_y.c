/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadri_get_y.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan-re <rchan-re@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:10:03 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/19 18:34:47 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS

# include "cub3d.h"

static int	is_left_complete(int i, t_game *game,
			t_quadri *quadri, int radius_map)
{
	int		y_idx;
	float	y_real;

	y_idx = radius_map;
	y_real = radius_map + game->player.pos_y - (int)(game->player.pos_y);
	if (i < y_idx
		&& y_real * game->scene.minimap_scale_screen_map
		- game->scene.minimap_radius_screen
		<= i * game->scene.minimap_scale_screen_map)
	{
		quadri->y_start = i * game->scene.minimap_scale_screen_map
			- (y_real * game->scene.minimap_scale_screen_map
				- game->scene.minimap_radius_screen);
		quadri->y_end = quadri->y_start + game->scene.minimap_scale_screen_map
			- 1;
		return (1);
	}
	return (0);
}

static int	else_is_left_partial(int i, t_game *game,
			t_quadri *quadri, int radius_map)
{
	int		y_idx;
	float	y_real;

	y_idx = radius_map;
	y_real = radius_map + game->player.pos_y - (int)(game->player.pos_y);
	if (i < y_idx
		&& y_real * game->scene.minimap_scale_screen_map
		- game->scene.minimap_radius_screen
		< (i + 1) * game->scene.minimap_scale_screen_map)
	{
		quadri->y_start = 0;
		quadri->y_end = (i + 1) * game->scene.minimap_scale_screen_map - 1
			- (y_real * game->scene.minimap_scale_screen_map
				- game->scene.minimap_radius_screen);
		return (1);
	}
	return (0);
}

static int	else_is_same_partial(int i, t_game *game,
			t_quadri *quadri, int radius_map)
{
	int		y_idx;
	float	y_real;

	y_idx = radius_map;
	y_real = radius_map + game->player.pos_y - (int)(game->player.pos_y);
	if (i == y_idx
		&& y_real * game->scene.minimap_scale_screen_map
		- game->scene.minimap_radius_screen
		> i * game->scene.minimap_scale_screen_map)
	{
		quadri->y_start = 0;
		quadri->y_end = y_real * game->scene.minimap_scale_screen_map - 1
			+ game->scene.minimap_radius_screen - 1;
		return (1);
	}
	return (0);
}

static int	else_is_right_complete(int i, t_game *game,
			t_quadri *quadri, int radius_map)
{
	int		y_idx;
	float	y_real;

	y_idx = radius_map;
	y_real = radius_map + game->player.pos_y - (int)(game->player.pos_y);
	if (i > y_idx
		&& y_real * game->scene.minimap_scale_screen_map
		+ game->scene.minimap_radius_screen
		>= (i + 1) * game->scene.minimap_scale_screen_map)
	{
		quadri->y_start = i * game->scene.minimap_scale_screen_map
			- (y_real * game->scene.minimap_scale_screen_map
				- game->scene.minimap_radius_screen);
		quadri->y_end = quadri->y_start + game->scene.minimap_scale_screen_map
			- 1;
		return (1);
	}
	return (0);
}

int	quadri_get_y(t_game *game, int i, t_quadri *quadri, int radius_map)
{
	int		y_player_index;
	float	y_player_real;

	y_player_index = radius_map;
	y_player_real = radius_map + game->player.pos_y - (int)(game->player.pos_y);
	if (is_left_complete(i, game, quadri, radius_map))
		return (1);
	else if (else_is_left_partial(i, game, quadri, radius_map))
		return (1);
	else if (else_is_same_partial(i, game, quadri, radius_map))
		return (1);
	else if (i == y_player_index)
	{
		quadri->y_start = i * game->scene.minimap_scale_screen_map
			- (y_player_real * game->scene.minimap_scale_screen_map
				- game->scene.minimap_radius_screen);
		return (quadri->y_end = quadri->y_start
			+ game->scene.minimap_scale_screen_map - 1, 1);
	}
	else if (else_is_right_complete(i, game, quadri, radius_map))
		return (1);
	quadri->y_start = i * game->scene.minimap_scale_screen_map
		- (y_player_real * game->scene.minimap_scale_screen_map
			- game->scene.minimap_radius_screen);
	return (quadri->y_end = 2 * game->scene.minimap_radius_screen - 1, 1);
}
#endif
