/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_mlx_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 10:55:58 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/15 14:31:30 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef BONUS

static int	t_mlx_textures_init(t_mlx *mlx, t_list *files[D + 1])
{
	int		i;
	t_list	*node_file;
	t_list	*node_img;

	i = 0;
	while (i < D + 1)
	{
		node_file = files[i];
		while (node_file != NULL)
		{
			node_img = ft_lstnew(NULL);
			if (node_img == NULL)
				return (0);
			node_img->content = malloc(sizeof(t_img));
			if (node_img->content == NULL)
				return (free(node_img), 0);
			if (!t_img_init_file(mlx->mlx_ptr, node_img->content,
					node_file->content))
				return (free(node_img->content), free(node_img), 0);
			ft_lstadd_back(&(mlx->textures[i]), node_img);
			node_file = node_file->next;
		}
		i++;
	}
	return (1);
}

int	t_mlx_init(t_mlx *mlx, t_list *files[D + 1])
{
	if (mlx == NULL)
		return (0);
	mlx->frame.img_ptr = NULL;
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		return (ft_dprintf (2, ERR_MLX_INIT), 0);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	if (mlx->win_ptr == NULL)
		return (ft_dprintf (2, ERR_MLX_NEW_WINDOW),
			mlx_destroy_display(mlx->mlx_ptr), free(mlx->mlx_ptr), 0);
	if (t_mlx_textures_init(mlx, files) == 0)
		return (t_mlx_free(mlx), 0);
	if (t_img_init(mlx->mlx_ptr, &(mlx->frame), WIDTH, HEIGHT) == 0)
		return (t_mlx_free(mlx), 0);
	return (1);
}

#else

static int	t_mlx_textures_init(t_mlx *mlx, t_list *files[4])
{
	int		i;
	t_list	*node_file;
	t_list	*node_img;

	i = 0;
	while (i < 4)
	{
		node_file = files[i];
		while (node_file != NULL)
		{
			node_img = ft_lstnew(NULL);
			if (node_img == NULL)
				return (0);
			node_img->content = malloc(sizeof(t_img));
			if (node_img->content == NULL)
				return (free(node_img), 0);
			if (!t_img_init_file(mlx->mlx_ptr, node_img->content,
					node_file->content))
				return (free(node_img->content), free(node_img), 0);
			ft_lstadd_back(&(mlx->textures[i]), node_img);
			node_file = node_file->next;
		}
		i++;
	}
	return (1);
}

int	t_mlx_init(t_mlx *mlx, t_list *files[4])
{
	if (mlx == NULL)
		return (0);
	mlx->frame.img_ptr = NULL;
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		return (ft_dprintf (2, ERR_MLX_INIT), 0);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	if (mlx->win_ptr == NULL)
		return (ft_dprintf (2, ERR_MLX_NEW_WINDOW),
			mlx_destroy_display(mlx->mlx_ptr), free(mlx->mlx_ptr), 0);
	if (t_mlx_textures_init(mlx, files) == 0)
		return (t_mlx_free(mlx), 0);
	if (t_img_init(mlx->mlx_ptr, &(mlx->frame), WIDTH, HEIGHT) == 0)
		return (t_mlx_free(mlx), 0);
	return (1);
}

#endif
