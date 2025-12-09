/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_down_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan-re <rchan-re@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:08:53 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/09 14:09:56 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef BONUS

int	key_down_hook(int keycode, void *param)
{
	if (keycode == XK_Left)
		(((t_game *)param)->key_press)[ARROW_LEFT] = 1;
	if (keycode == XK_Right)
		(((t_game *)param)->key_press)[ARROW_RIGHT] = 1;
	if (keycode == XK_s)
		(((t_game *)param)->key_press)[MOVE_DOWN] = 1;
	if (keycode == XK_w)
		(((t_game *)param)->key_press)[MOVE_UP] = 1;
	if (keycode == XK_a)
		(((t_game *)param)->key_press)[MOVE_LEFT] = 1;
	if (keycode == XK_d)
		(((t_game *)param)->key_press)[MOVE_RIGHT] = 1;
	return (1);
}

#else

int	key_down_hook(int keycode, void *param)
{
	if (keycode == XK_Left)
		(((t_game *)param)->key_press)[ARROW_LEFT] = 1;
	if (keycode == XK_Right)
		(((t_game *)param)->key_press)[ARROW_RIGHT] = 1;
	if (keycode == XK_s)
		(((t_game *)param)->key_press)[MOVE_DOWN] = 1;
	if (keycode == XK_w)
		(((t_game *)param)->key_press)[MOVE_UP] = 1;
	if (keycode == XK_a)
		(((t_game *)param)->key_press)[MOVE_LEFT] = 1;
	if (keycode == XK_d)
		(((t_game *)param)->key_press)[MOVE_RIGHT] = 1;
	return (1);
}

#endif
