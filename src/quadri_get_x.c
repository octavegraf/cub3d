/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadri_get_x.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan-re <rchan-re@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:08:11 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/24 14:48:48 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS

# include "cub3d.h"

static int	is_above_complete(int i, t_game *game,
			t_quadri *quadri, int radius_map)
{
	int		x_idx;
	float	x_real;

	x_idx = radius_map;
	x_real = radius_map + game->player.pos_x - (int)(game->player.pos_x);
	if (i < x_idx
		&& x_real * game->scene.minimap_scale_screen_map
		- game->scene.minimap_radius_screen
		<= i * game->scene.minimap_scale_screen_map)
	{
		quadri->x_start = i * game->scene.minimap_scale_screen_map
			- (x_real * game->scene.minimap_scale_screen_map
				- game->scene.minimap_radius_screen);
		quadri->x_end = quadri->x_start + game->scene.minimap_scale_screen_map
			- 1;
		return (1);
	}
	return (0);
}

static int	else_is_above_partial(int i, t_game *game,
			t_quadri *quadri, int radius_map)
{
	int		x_idx;
	float	x_real;

	x_idx = radius_map;
	x_real = radius_map + game->player.pos_x - (int)(game->player.pos_x);
	if (i < x_idx
		&& x_real * game->scene.minimap_scale_screen_map
		- game->scene.minimap_radius_screen
		< (i + 1) * game->scene.minimap_scale_screen_map)
	{
		quadri->x_start = 0;
		quadri->x_end = (i + 1) * game->scene.minimap_scale_screen_map - 1
			- (x_real * game->scene.minimap_scale_screen_map
				- game->scene.minimap_radius_screen);
		return (1);
	}
	return (0);
}

static int	else_is_same_partial(int i, t_game *game,
			t_quadri *quadri, int radius_map)
{
	int		x_idx;
	float	x_real;

	x_idx = radius_map;
	x_real = radius_map + game->player.pos_x - (int)(game->player.pos_x);
	if (i == x_idx
		&& x_real * game->scene.minimap_scale_screen_map
		- game->scene.minimap_radius_screen
		> i * game->scene.minimap_scale_screen_map)
	{
		quadri->x_start = 0;
		quadri->x_end = x_real * game->scene.minimap_scale_screen_map - 1
			+ game->scene.minimap_radius_screen - 1;
		return (1);
	}
	return (0);
}

static int	else_is_under_complete(int i, t_game *game,
			t_quadri *quadri, int radius_map)
{
	int		x_idx;
	float	x_real;

	x_idx = radius_map;
	x_real = radius_map + game->player.pos_x - (int)(game->player.pos_x);
	if (i > x_idx
		&& x_real * game->scene.minimap_scale_screen_map
		+ game->scene.minimap_radius_screen
		>= (i + 1) * game->scene.minimap_scale_screen_map)
	{
		quadri->x_start = i * game->scene.minimap_scale_screen_map
			- (x_real * game->scene.minimap_scale_screen_map
				- game->scene.minimap_radius_screen);
		quadri->x_end = quadri->x_start + game->scene.minimap_scale_screen_map
			- 1;
		return (1);
	}
	return (0);
}

void	quadri_get_x(t_game *g, int i, t_quadri *quadri, int radius_map)
{
	int		x_player_index;
	float	x_player_real;

	x_player_index = radius_map;
	x_player_real = radius_map + g->player.pos_x - (int)(g->player.pos_x);
	if (is_above_complete(i, g, quadri, radius_map))
		return ;
	else if (else_is_above_partial(i, g, quadri, radius_map))
		return ;
	else if (else_is_same_partial(i, g, quadri, radius_map))
		return ;
	else if (i == x_player_index)
	{
		quadri->x_start = i * g->scene.minimap_scale_screen_map
			- (x_player_real * g->scene.minimap_scale_screen_map
				- g->scene.minimap_radius_screen);
		quadri->x_end = quadri->x_start + g->scene.minimap_scale_screen_map - 1;
		return ;
	}
	else if (else_is_under_complete(i, g, quadri, radius_map))
		return ;
	quadri->x_start = i * g->scene.minimap_scale_screen_map
		- (x_player_real * g->scene.minimap_scale_screen_map
			- g->scene.minimap_radius_screen);
	quadri->x_end = 2 * g->scene.minimap_radius_screen - 1;
}

#endif
