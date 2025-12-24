/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadri_fill_minimap.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan-re <rchan-re@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:35:59 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/12 19:12:57 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS

# include "cub3d.h"

void	fill_quadri_minimap(t_game *game, t_quadri *quadri)
{
	int	x;
	int	y;

	x = quadri->x_start;
	while (x <= quadri->x_end)
	{
		y = quadri->y_start;
		while (y <= quadri->y_end)
		{
			img_fill_pixel(game->mlx.frame, y, x, quadri->color);
			y++;
		}
		x++;
	}
}

#endif 
