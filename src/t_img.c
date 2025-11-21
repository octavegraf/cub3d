/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_img.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:43:24 by rchan-re          #+#    #+#             */
/*   Updated: 2025/11/21 18:43:26 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	t_img_init(void *mlx_ptr, t_img *img, int width, int height)
{
	if (img == NULL)
		return (0);
	img->mlx_ptr = mlx_ptr;
	img->img_ptr = mlx_new_image(mlx_ptr, width, height);
	if (img->img_ptr == NULL)
		return (ft_dprintf (2, ERR_MLX_NEW_IMAGE), 0);
	img->buf = mlx_get_data_addr(img->img_ptr, &(img->bpp),
			&(img->size_line), &(img->endian));
	if (img->buf == NULL)
	{
		ft_dprintf (2, ERR_MLX_GET_DATA_ADDR);
		mlx_destroy_image(mlx_ptr, img->img_ptr);
		img->img_ptr = NULL;
		return (0);
	}
	img->bpp /= 8;
	return (1);
}

int	t_img_init_file(void *mlx_ptr, t_img *img, char *file)
{
	if (img == NULL)
		return (0);
	img->mlx_ptr = mlx_ptr;
	img->img_ptr = mlx_xpm_file_to_image(mlx_ptr, file, &(img->w), &(img->h));
	if (img->img_ptr == NULL)
		return (ft_dprintf (2, ERR_MLX_XPM_FILE), 0);
	img->buf = mlx_get_data_addr(img->img_ptr, &(img->bpp),
			&(img->size_line), &(img->endian));
	if (img->buf == NULL)
		return (ft_dprintf (2, ERR_MLX_GET_DATA_ADDR),
			mlx_destroy_image(mlx_ptr, img->img_ptr),
			img->img_ptr = NULL, 0);
	img->bpp /= 8;
	return (1);
}
