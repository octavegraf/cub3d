/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_fill_pixel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan-re <rchan-re@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:43:24 by rchan-re          #+#    #+#             */
/*   Updated: 2025/11/11 17:43:24 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_fill_pixel(t_img img, int x, int y, unsigned int color)
{
	int		i;	

	color = mlx_get_color_value(img.mlx_ptr, color);
	i = 0;
	while (i < img.bpp)
	{
		if (img.endian == 0)
			img.buf[y * img.size_line + img.bpp * x + i] = (color >> (i * 8));
		else
			img.buf[y * img.size_line + img.bpp * x + i]
				= (color >> ((img.bpp - 1 - i) * 8));
		i++;
	}
}

void	img_fill_ceiling_floor(t_game *game, int x, int y)
{
	if (y < HEIGHT / 2)
		img_fill_pixel(game->mlx.frame, x, y, game->scene.ceiling_color);
	else
		img_fill_pixel(game->mlx.frame, x, y, game->scene.floor_color);
}

void	raycast_fill_img(t_game *game, int x, int y, t_raycast *raycast)
{
	raycast->tex_y = ((int)raycast->tex_pos) & (raycast->texture->h - 1);
	raycast->tex_pos += raycast->step;
	ft_memcpy(game->mlx.frame.buf
		+ ((game->mlx.frame.size_line * y) + x * game->mlx.frame.bpp),
		raycast->texture->buf + ((raycast->texture->size_line * raycast->tex_y)
			+ raycast->tex_x * raycast->texture->bpp), game->mlx.frame.bpp);
}
