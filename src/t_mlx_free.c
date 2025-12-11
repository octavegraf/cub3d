/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_mlx_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:43:24 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/11 11:00:50 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	t_img_free(t_img *img)
{
	if (img == NULL)
		return ;
	if (img->img_ptr != NULL)
	{
		mlx_destroy_image(img->mlx_ptr, img->img_ptr);
		img->img_ptr = NULL;
	}
}

static void	t_node_img_free(void *img)
{
	t_img_free(img);
	free(img);
}

void	t_mlx_free(t_mlx *mlx)
{
	int		i;
	t_list	*node_img;

	(void)node_img;
	if (mlx->mlx_ptr == NULL)
		return ;
	t_img_free(&(mlx->frame));
	i = 0;
	while (i < 4)
	{
		node_img = mlx->textures[i];
		ft_lstclear(&(mlx->textures[i]), t_node_img_free);
		i++;
	}
	if (mlx->win_ptr != NULL)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx->win_ptr = NULL;
	}
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	mlx->mlx_ptr = NULL;
}
