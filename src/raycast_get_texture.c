/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_get_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:08:32 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/12 15:11:41 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef BONUS

static void	update_texture(t_list **node_img, t_list *head_img,
		struct timeval *tv_old, struct timeval *tv)
{
	if (*node_img == NULL)
		*node_img = head_img;
	else if (diff_time_tv(tv_old, tv) != 0)
	{
		*node_img = (*node_img)->next;
		if (*node_img == NULL)
			*node_img = head_img;
	}
}
static int	assign_texture2(t_game *game, t_raycast *raycast,
				t_list *textures[D + 1], int n);

static int	assign_texture(t_game *g, t_raycast *rc,
	t_list *textures[D + 1], int n)
{
	if (rc->side == 0)
	{
		if (rc->ray_dir_x < 0)
		{
			if (g->scene.map[rc->map_x + 1][rc->map_y] == c_u)
				rc->texture = textures[D]->content;
			else if (n == 2 && g->scene.map[rc->map_x][rc->map_y] == d_l_u)
				return (rc->texture = textures[D]->content, d_l_u);
			else
				rc->texture = textures[NO]->content;
		}
		else
		{
			if (g->scene.map[rc->map_x][rc->map_y] == c_u)
				rc->texture = textures[D]->content;
			else if (n == 2 && g->scene.map[rc->map_x][rc->map_y] == d_l_d)
				return (rc->texture = textures[D]->content, d_l_d);
			else
				rc->texture = textures[SO]->content;
		}
	}
	else
		return (assign_texture2(g, rc, textures, n));
	return ('1');
}

static int	assign_texture2(t_game *g, t_raycast *rc,
				t_list *textures[D + 1], int n)
{
	{
		if (rc->ray_dir_y < 0)
		{
			if (g->scene.map[rc->map_x][rc->map_y + 1] == c_l)
				rc->texture = textures[D]->content;
			else if (n == 2 && g->scene.map[rc->map_x][rc->map_y] == d_u_l)
				return (rc->texture = textures[D]->content, d_u_l);
			else
				rc->texture = textures[WE]->content;
		}
		else
		{
			if (g->scene.map[rc->map_x][rc->map_y] == c_l)
				rc->texture = textures[D]->content;
			else if (n == 2 && g->scene.map[rc->map_x][rc->map_y] == d_u_r)
				return (rc->texture = textures[D]->content, d_u_r);
			else
				rc->texture = textures[EA]->content;
		}
	}
	return ('1');
}

int	raycast_get_texture(t_game *game, t_raycast *raycast, struct timeval *tv,
	int n)
{
	static t_list	*textures[D + 1] = {0};
	int				i;

	i = 0;
	while (i <= D)
	{
		update_texture(&(textures[i]), game->mlx.textures[i], &(game->tv), tv);
		i++;
	}
	if (diff_time_tv(&(game->tv), tv) != 0)
		update_time_tv(&(game->tv), FREQ_SEC, FREQ_USEC);
	return (assign_texture(game, raycast, textures, n));
}
#else

void	raycast_get_texture(t_game *game, t_raycast *raycast)
{
	int				i;

	i = 0;
	if (raycast->side == 0)
	{
		if (raycast->ray_dir_x < 0)
			raycast->texture = game->mlx.textures[NO]->content;
		else
			raycast->texture = game->mlx.textures[SO]->content;
	}
	else
	{
		if (raycast->ray_dir_y < 0)
			raycast->texture = game->mlx.textures[WE]->content;
		else
			raycast->texture = game->mlx.textures[EA]->content;
	}
}
#endif
