/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:43:24 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/12 13:42:29 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#ifdef BONUS

int	display_frame(void *param)
{
	t_game	*game;

	game = param;
	mlx_mouse_hide(game->mlx.mlx_ptr, game->mlx.win_ptr);
	mlx_mouse_move(game->mlx.mlx_ptr, game->mlx.win_ptr, WIDTH / 2, HEIGHT / 2);
	if (raycast(game, 1) == 0)
		return (mlx_loop_end(((t_mlx *)param)->mlx_ptr));
	if (raycast(game, 2) == 0)
		return (mlx_loop_end(((t_mlx *)param)->mlx_ptr));
	if (game->key_press[MINIMAP_HIDE] == 1
		&& display_minimap(game, game->scene.minimap_radius_map) == 0)
		return (mlx_loop_end(((t_mlx *)param)->mlx_ptr));
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr, \
			game->mlx.frame.img_ptr, 0, 0);
	return (1);
}
#else

int	display_frame(void *param)
{
	t_game	*game;

	game = param;
	if (raycast(game) == 0)
		return (mlx_loop_end(((t_mlx *)param)->mlx_ptr));
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr, \
		game->mlx.frame.img_ptr, 0, 0);
	return (1);
}
#endif
