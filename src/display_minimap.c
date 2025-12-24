/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:57:29 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/24 14:51:08 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef BONUS

static void	draw_quadri_minimap(t_game *game, char **minimap, int radius_map)
{
	int			i;
	int			j;
	t_quadri	quadri;

	i = 0;
	j = 0;
	while (i < (radius_map * 2) + 1)
	{
		quadri_get_x(game, i, &quadri, radius_map);
		j = 0;
		while (j < (radius_map * 2) + 1)
		{
			quadri_get_y(game, j, &quadri, radius_map);
			quadri.color = BLACK;
			if (e_chr_white(minimap[i][j]))
				quadri.color = WHITE;
			fill_quadri_minimap(game, &quadri);
			j++;
		}
		i++;
	}
}

static void	draw_outline_minimap(t_game *game, int radius_map)
{
	t_quadri	quadri;

	quadri.color = GREEN;
	quadri.x_start = 0;
	quadri.x_end = (radius_map * 2 * game->scene.minimap_scale_screen_map) - 1;
	quadri.y_start = 0;
	quadri.y_end = 0;
	fill_quadri_minimap(game, &quadri);
	quadri.x_start = 0;
	quadri.x_end = 0;
	quadri.y_start = 0;
	quadri.y_end = (radius_map * 2 * game->scene.minimap_scale_screen_map) - 1;
	fill_quadri_minimap(game, &quadri);
	quadri.x_start = 0;
	quadri.x_end = (radius_map * 2 * game->scene.minimap_scale_screen_map) - 1;
	quadri.y_start = (radius_map * 2 * game->scene.minimap_scale_screen_map)
		- 1;
	quadri.y_end = (radius_map * 2 * game->scene.minimap_scale_screen_map) - 1;
	fill_quadri_minimap(game, &quadri);
	quadri.x_start = (radius_map * 2 * game->scene.minimap_scale_screen_map)
		- 1;
	quadri.x_end = (radius_map * 2 * game->scene.minimap_scale_screen_map) - 1;
	quadri.y_start = 0;
	quadri.y_end = (radius_map * 2 * game->scene.minimap_scale_screen_map) - 1;
	fill_quadri_minimap(game, &quadri);
}

static int	is_valid_quadri(t_quadri *quadri)
{
	if (quadri->x_start < 0 || quadri->x_start >= HEIGHT)
		return (0);
	if (quadri->x_end < 0 || quadri->x_end >= HEIGHT)
		return (0);
	if (quadri->x_start > quadri->x_end)
		return (0);
	if (quadri->y_start < 0 || quadri->y_start >= WIDTH)
		return (0);
	if (quadri->y_end < 0 || quadri->y_end >= WIDTH)
		return (0);
	if (quadri->y_start > quadri->y_end)
		return (0);
	return (1);
}

int	display_minimap(t_game *game, int radius_map)
{
	t_quadri	quadri;

	if (minimap_get(game, radius_map) == 0)
		return (0);
	draw_quadri_minimap(game, game->scene.minimap, radius_map);
	quadri.x_start = radius_map * game->scene.minimap_scale_screen_map
		- SIZE_PLAYER;
	quadri.x_end = radius_map * game->scene.minimap_scale_screen_map
		+ SIZE_PLAYER;
	quadri.y_start = radius_map * game->scene.minimap_scale_screen_map
		- SIZE_PLAYER;
	quadri.y_end = radius_map * game->scene.minimap_scale_screen_map
		+ SIZE_PLAYER;
	if (SIZE_PLAYER <= 0 || is_valid_quadri(&quadri) == 0)
		return (ft_dprintf(2, ERR_MINIMAP_PLAYER), 0);
	quadri.color = RED;
	fill_quadri_minimap(game, &quadri);
	draw_doors(game, radius_map);
	draw_player_fov_minimap(game, radius_map);
	draw_outline_minimap(game, radius_map);
	minimap_free(&(game->scene.minimap), (radius_map * 2) + 1, radius_map);
	return (1);
}
#endif
