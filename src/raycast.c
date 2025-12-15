/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:43:24 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/12 18:02:49 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef BONUS

static int	raycast_param(t_game *g, t_raycast *rc, struct timeval *tv, int n)
{
	int	res;

	res = raycast_compute(g, rc, tv, n);
	if (n == 2 && res == '1')
		return (HEIGHT);
	if ((res == d_u_l || res == d_l_d) && rc->tex_x < rc->texture->w / 2)
		return (HEIGHT);
	if ((res == d_u_r || res == d_l_u) && rc->tex_x > rc->texture->w / 2)
		return (HEIGHT);
	return (0);
}

int	raycast(t_game *game, int n)
{
	int				x;
	int				y;
	t_raycast		raycast;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (ft_dprintf(2, ERR_GETTIMEOFDAY), 0);
	x = 0;
	while (x < WIDTH)
	{
		raycast_init(&raycast, game, x);
		y = raycast_param(game, &raycast, &tv, n);
		while (y < HEIGHT)
		{
			if (raycast.draw_start <= y && y <= raycast.draw_end)
				raycast_fill_img(game, x, y, &raycast);
			else if (n == 1)
				img_fill_ceiling_floor(game, x, y);
			y++;
		}
		x++;
	}
	return (1);
}

#else

int	raycast(t_game *game)
{
	int				x;
	int				y;
	t_raycast		raycast;

	game_update_moves(game);
	x = 0;
	while (x < WIDTH)
	{
		raycast_compute(x, game, &raycast);
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
#endif
