/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_mlx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:43:24 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/02 13:51:22 by ocgraf           ###   ########.fr       */
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
				return (free(node_img), 0); // FREE
			if (!t_img_init_file(mlx->mlx_ptr, node_img->content,
					node_file->content))
				return (free(node_img), 0);
			ft_lstadd_back(&(mlx->textures[i]), node_img);
			node_file = node_file->next;
		}
		i++;
	}
	return (1);
}
/*
static int	t_mlx_textures_init(t_mlx *mlx, char *files[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx->textures[i].img_ptr = NULL;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (t_img_init_file(mlx->mlx_ptr, &(mlx->textures[i]), files[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}*/

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

void	t_mlx_free(t_mlx *mlx)
{
	int		i;
	t_list	*node_img;
	//t_list	*tmp;

	if (mlx->mlx_ptr == NULL)
		return ;
	t_img_free(&(mlx->frame));
	i = 0;
	while (i < 4)
	{
		node_img = mlx->textures[i];
		ft_lstclear(&(mlx->textures[i]), t_node_img_free);
		/*while (node_img != NULL)
		{
			t_img_free(node_img->content);
			free(node_img->content);
			tmp = node_img;
			node_img = node_img->next;
			free(tmp);
		}*/
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
