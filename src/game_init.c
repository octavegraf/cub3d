/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:43:24 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/09 12:22:17 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef BONUS

int	game_init(t_game *game)
{
	game->player = player_init(game->scene.map);
	if (MIN_DIM_RATIO > 1 || RADIUS_MAP <= 0)
		return (t_scene_free(&(game->scene)), 0);
	game_minimap_set_params(game, RADIUS_MAP, MIN_DIM_RATIO);
	if (t_mlx_init(&(game->mlx), game->scene.textures) == 0)
		return (t_scene_free(&(game->scene)), 0);
	ft_memset(game->key_press, 0, 8);
	game->key_press[MINIMAP_HIDE] = 1;
	game->key_press[MINIMAP_MAXIMIZE] = 1;
	game->scene.minimap = NULL;
	return (1);
}

#else

int	game_init(t_game *game)
{
	game->player = player_init(game->scene.map);
	if (t_mlx_init(&(game->mlx), game->scene.textures) == 0)
		return (t_scene_free(&(game->scene)), 0);
	ft_memset(game->key_press, 0, 6);
	return (1);
}
#endif
