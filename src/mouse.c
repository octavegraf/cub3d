/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:56:28 by ocgraf            #+#    #+#             */
/*   Updated: 2025/12/15 14:24:47 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#ifdef BONUS

int	mouse(int x, int y, void *param)
{
	t_game	*game;
	float	value;

	(void)y;
	game = (t_game *)param;
	if (!game)
		return (0);
	game->mouse_move[MOUSE_LEFT] = 0;
	game->mouse_move[MOUSE_RIGHT] = 0;
	value = (x - (WIDTH / 2)) * MOUSE_SENSITIVITY * 0.01;
	if (value < 0)
		game->mouse_move[MOUSE_LEFT] = -value;
	else if (value > 0)
		game->mouse_move[MOUSE_RIGHT] = value;
	return (0);
}

int	click(int click_hook, int x, int y, void *param)
{
	t_game	*game;

	(void)x;
	(void)y;
	game = (t_game *)param;
	key_up_hook(click_hook, game);
	return (0);
}

#endif