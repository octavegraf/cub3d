/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_set_params.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan-re <rchan-re@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:16:17 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/09 12:16:45 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS

# include "cub3d.h"

void	game_minimap_set_params(t_game *game, int radius, float min_dim_ratio)
{
	if (HEIGHT < WIDTH)
		game->scene.minimap_scale_screen_map = HEIGHT * min_dim_ratio
			/ (2 * radius);
	else
		game->scene.minimap_scale_screen_map = WIDTH * min_dim_ratio
			/ (2 * radius);
	game->scene.minimap_radius_screen = radius
		* game->scene.minimap_scale_screen_map;
	game->scene.minimap_radius_map = radius;
}

#endif
