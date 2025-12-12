/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:43:24 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/12 14:52:28 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef BONUS

static void	resolve_hit(t_raycast *raycast, t_game *game, int *hit)
{
	if (game->scene.map[raycast->map_x][raycast->map_y] == '1')
		*hit = 1;
	else if (ft_strchr(HIT_OPEN,
			game->scene.map[raycast->map_x][raycast->map_y]) != NULL)
		*hit = 1;
	else if (raycast->side == 0)
	{
		if (raycast->ray_dir_x > 0
			&& game->scene.map[raycast->map_x][raycast->map_y] == c_u)
			*hit = 1;
		else if (raycast->ray_dir_x < 0
			&& game->scene.map[raycast->map_x + 1][raycast->map_y] == c_u)
			*hit = 1;
	}
	else
	{
		if (raycast->ray_dir_y > 0
			&& game->scene.map[raycast->map_x][raycast->map_y] == c_l)
			*hit = 1;
		else if (raycast->ray_dir_y < 0
			&& game->scene.map[raycast->map_x][raycast->map_y + 1] == c_l)
			*hit = 1;
	}
}

void	raycast_dda(t_raycast *raycast, t_game *game)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (raycast->side_dist_x < raycast->side_dist_y)
		{
			raycast->side_dist_x += raycast->delta_dist_x;
			raycast->map_x += raycast->step_x;
			raycast->side = 0;
		}
		else
		{
			raycast->side_dist_y += raycast->delta_dist_y;
			raycast->map_y += raycast->step_y;
			raycast->side = 1;
		}
		resolve_hit(raycast, game, &hit);
	}
}

#else

void	raycast_dda(t_raycast *raycast, t_game *game)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (raycast->side_dist_x < raycast->side_dist_y)
		{
			raycast->side_dist_x += raycast->delta_dist_x;
			raycast->map_x += raycast->step_x;
			raycast->side = 0;
		}
		else
		{
			raycast->side_dist_y += raycast->delta_dist_y;
			raycast->map_y += raycast->step_y;
			raycast->side = 1;
		}
		if (game->scene.map[raycast->map_x][raycast->map_y] == '1')
			hit = 1;
	}
}

#endif
