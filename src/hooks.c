/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:43:24 by rchan-re          #+#    #+#             */
/*   Updated: 2025/11/22 09:14:30 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	key_down_hook(int keycode, void *param)
{
	if (keycode == KEY_LEFT)
		(((t_game *)param)->key_press)[ARROW_LEFT] = 1;
	if (keycode == KEY_RIGHT)
		(((t_game *)param)->key_press)[ARROW_RIGHT] = 1;
	if (keycode == KEY_S)
		(((t_game *)param)->key_press)[MOVE_DOWN] = 1;
	if (keycode == KEY_W)
		(((t_game *)param)->key_press)[MOVE_UP] = 1;
	if (keycode == KEY_A)
		(((t_game *)param)->key_press)[MOVE_LEFT] = 1;
	if (keycode == KEY_D)
		(((t_game *)param)->key_press)[MOVE_RIGHT] = 1;
	return (1);
}

int	close_window(void *param)
{
	return (mlx_loop_end(((t_mlx *)param)->mlx_ptr));
}
