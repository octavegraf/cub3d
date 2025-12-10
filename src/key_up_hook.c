/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_up_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:43:24 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/10 12:02:22 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef BONUS

static void	minimap_hook(int keycode, t_game *game)
{
	if (keycode == KEY_H)
		(game->key_press)[MINIMAP_HIDE] = 1 - game->key_press[MINIMAP_HIDE];
	if (keycode == KEY_M)
	{
		(game->key_press)[MINIMAP_MAXIMIZE] = 1
			- game->key_press[MINIMAP_MAXIMIZE];
		game_minimap_set_params(game,
			RADIUS_MAP + game->key_press[MINIMAP_MAXIMIZE] * RADIUS_MAP,
			MIN_DIM_RATIO + game->key_press[MINIMAP_MAXIMIZE] * MIN_DIM_RATIO);
	}
}

int	key_up_hook(int keycode, void *param)
{
	t_game	*game;

	game = param;
	if (keycode == KEY_ESC)
		return (mlx_loop_end(game->mlx.mlx_ptr));
	if (keycode == KEY_LEFT)
		(game->key_press)[ARROW_LEFT] = 0;
	if (keycode == KEY_RIGHT)
		(game->key_press)[ARROW_RIGHT] = 0;
	if (keycode == KEY_S)
		(game->key_press)[MOVE_DOWN] = 0;
	if (keycode == KEY_W)
		(game->key_press)[MOVE_UP] = 0;
	if (keycode == KEY_A)
		(game->key_press)[MOVE_LEFT] = 0;
	if (keycode == KEY_D)
		(game->key_press)[MOVE_RIGHT] = 0;
	minimap_hook(keycode, game);
	return (0);
}

#else

int	key_up_hook(int keycode, void *param)
{
	if (keycode == KEY_ESC)
		return (mlx_loop_end(((t_game *)param)->mlx.mlx_ptr));
	if (keycode == KEY_LEFT)
		(((t_game *)param)->key_press)[ARROW_LEFT] = 0;
	if (keycode == KEY_RIGHT)
		(((t_game *)param)->key_press)[ARROW_RIGHT] = 0;
	if (keycode == KEY_S)
		(((t_game *)param)->key_press)[MOVE_DOWN] = 0;
	if (keycode == KEY_W)
		(((t_game *)param)->key_press)[MOVE_UP] = 0;
	if (keycode == KEY_A)
		(((t_game *)param)->key_press)[MOVE_LEFT] = 0;
	if (keycode == KEY_D)
		(((t_game *)param)->key_press)[MOVE_RIGHT] = 0;
	return (0);
}

#endif
