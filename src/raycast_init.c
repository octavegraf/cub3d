/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan-re <rchan-re@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:43:24 by rchan-re          #+#    #+#             */
/*   Updated: 2025/11/11 17:43:24 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	raycast_init_step(t_raycast *rc, t_game *game)
{
	if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (game->player.pos_x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - game->player.pos_x)
			* rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (game->player.pos_y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - game->player.pos_y)
			* rc->delta_dist_y;
	}
}

void	raycast_init(t_raycast *raycast, t_game *game, int x)
{
	raycast->camera_x = 2 * x / (double)WIDTH - 1;
	raycast->ray_dir_x = game->player.dir_x
		+ game->player.plane_x * raycast->camera_x;
	raycast->ray_dir_y = game->player.dir_y
		+ game->player.plane_y * raycast->camera_x;
	raycast->map_x = (int)game->player.pos_x;
	raycast->map_y = (int)game->player.pos_y;
	if (raycast->ray_dir_x == 0)
		raycast->delta_dist_x = 1e30;
	else if (raycast->ray_dir_x > 0)
		raycast->delta_dist_x = 1 / raycast->ray_dir_x;
	else
		raycast->delta_dist_x = -1 / raycast->ray_dir_x;
	if (raycast->ray_dir_y == 0)
		raycast->delta_dist_y = 1e30;
	else if (raycast->ray_dir_y > 0)
		raycast->delta_dist_y = 1 / raycast->ray_dir_y;
	else
		raycast->delta_dist_y = -1 / raycast->ray_dir_y;
	raycast_init_step(raycast, game);
}
