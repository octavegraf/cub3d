/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:43:24 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/05 17:36:10 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	t_scene_free(t_scene scene)
{
	int	i;

	if (scene.map != NULL)
	{
		i = 0;
		while (scene.map[i] != NULL)
		{
			free(scene.map[i]);
			i++;
		}
		free(scene.map);
	}
	i = 0;
	while (i < 4)
	{
		ft_lstclear(&scene.textures[i], free);
		i++;
	}
}

int	game_init(t_game *game)
{
	game->player = player_init(game->scene.map);
	if (MIN_DIM_RATIO > 1 || RADIUS_MAP <= 0 )
		return (t_scene_free(game->scene), 0);
	if (HEIGHT < WIDTH)
		game->minimap_scale_screen_map = HEIGHT * MIN_DIM_RATIO / (2 * RADIUS_MAP);
	else
		game->minimap_scale_screen_map = WIDTH * MIN_DIM_RATIO / (2 * RADIUS_MAP);
	game->minimap_radius_screen = RADIUS_MAP * game->minimap_scale_screen_map;
	if (t_mlx_init(&(game->mlx), game->scene.textures) == 0)
		return (t_scene_free(game->scene), 0);
	ft_memset(game->key_press, 0, 6);
	return (1);
}

void	game_free(t_game game)
{
	t_mlx_free(&(game.mlx));
	t_scene_free(game.scene);
	get_next_line(-1);
}
