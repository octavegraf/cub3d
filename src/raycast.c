/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan-re <rchan-re@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:43:24 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/11 11:31:34 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	raycast(t_game *game)
{
	int				x;
	int				y;
	t_raycast		raycast;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (ft_dprintf(2, ERR_GETTIMEOFDAY), 0);
	game_update_moves(game);
	x = 0;
	while (x < WIDTH)
	{
		raycast_compute(x, game, &raycast, &tv);
		y = 0;
		while (y < HEIGHT)
		{
			if (raycast.draw_start <= y && y <= raycast.draw_end)
				raycast_fill_img(game, x, y, &raycast);
			else
				img_fill_ceiling_floor(game, x, y);
			y++;
		}
		x++;
	}
	return (1);
}
