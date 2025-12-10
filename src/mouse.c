/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:56:28 by ocgraf            #+#    #+#             */
/*   Updated: 2025/12/10 14:09:52 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "cub3d.h"

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
#endif