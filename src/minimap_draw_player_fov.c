/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw_player_fov.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan-re <rchan-re@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:14:16 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/09 16:47:27 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS

# include "cub3d.h"

static int	fov_ray_in_minimap(t_game *game, int radius_map,
		int ray_x, int ray_y)
{
	int	coord_x;
	int	coord_y;

	coord_x = radius_map * game->scene.minimap_scale_screen_map + ray_x;
	coord_y = radius_map * game->scene.minimap_scale_screen_map + ray_y;
	if (coord_x >= 0
		&& coord_x < radius_map * 2 * game->scene.minimap_scale_screen_map + 1
		&& coord_y >= 0
		&& coord_y < radius_map * 2 * game->scene.minimap_scale_screen_map + 1)
		return (1);
	return (0);
}

static int	draw_fov_in_minimap(t_game *game, t_quadri *quadri, int radius_map)
{
	int	res;

	res = 0;
	if (fov_ray_in_minimap(game, radius_map, quadri->x_start, quadri->y_start))
	{
		res = 1;
		img_fill_pixel(game->mlx.frame,
			radius_map * game->scene.minimap_scale_screen_map + quadri->y_start,
			radius_map * game->scene.minimap_scale_screen_map + quadri->x_start,
			BLUE);
	}
	if (fov_ray_in_minimap(game, radius_map, quadri->x_end, quadri->y_end))
	{
		res = 1;
		img_fill_pixel(game->mlx.frame,
			radius_map * game->scene.minimap_scale_screen_map + quadri->y_end,
			radius_map * game->scene.minimap_scale_screen_map + quadri->x_end,
			BLUE);
	}
	return (res);
}

static void	update_ray_x(t_game *game, int i, int *ray_x_1, int *ray_x_2)
{
	*ray_x_1 = (game->player.dir_x - game->player.plane_x)
		* game->scene.minimap_scale_screen_map * i * MINIMAP_FOV_STEP;
	*ray_x_2 = (game->player.dir_x + game->player.plane_x)
		* game->scene.minimap_scale_screen_map * i * MINIMAP_FOV_STEP;
}

static void	update_ray_y(t_game *game, int i, int *ray_y_1, int *ray_y_2)
{
	*ray_y_1 = (game->player.dir_y - game->player.plane_y)
		* game->scene.minimap_scale_screen_map * i * MINIMAP_FOV_STEP;
	*ray_y_2 = (game->player.dir_y + game->player.plane_y)
		* game->scene.minimap_scale_screen_map * i * MINIMAP_FOV_STEP;
}

void	draw_player_fov_minimap(t_game *game, int radius_map)
{
	t_quadri	quadri;
	int			i;

	i = 0;
	update_ray_x(game, i, &(quadri.x_start), &(quadri.x_end));
	update_ray_y(game, i, &(quadri.y_start), &(quadri.y_end));
	while (draw_fov_in_minimap(game, &quadri, radius_map))
	{
		update_ray_x(game, i, &(quadri.x_start), &(quadri.x_end));
		update_ray_y(game, i, &(quadri.y_start), &(quadri.y_end));
		i++;
	}
}
#endif
