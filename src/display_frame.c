/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan-re <rchan-re@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:43:24 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/02 16:17:35 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	display_frame(void *param)
{
	t_game	*game;

	game = param;
	if (raycast(game) == 0)
		return (0);
	if (display_minimap(game) == 0)
		return (0);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr, \
			game->mlx.frame.img_ptr, 0, 0);
	return (1);
}
