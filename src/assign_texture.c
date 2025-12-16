/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:38:41 by ocgraf            #+#    #+#             */
/*   Updated: 2025/12/16 14:39:50 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#ifdef BONUS

static int	assign_texture2(t_game *game, t_raycast *raycast,
				t_list *textures[D + 1], int n);

static int	assign_texture_sprite(t_game *g, t_raycast *rc,
	t_list *textures[D + 1], int n)
{
	if (rc->side == 0)
	{
		if (rc->ray_dir_x < 0)
		{
			if (n == 3 && g->scene.map[rc->map_x + 1][rc->map_y] == t)
				return (rc->texture = textures[T]->content, t);
		}
		else
		{
			if (n == 3 && g->scene.map[rc->map_x][rc->map_y] == t)
				return (rc->texture = textures[T]->content, t);
		}
	}
	return (0);
}

int	assign_texture(t_game *g, t_raycast *rc, t_list *textures[D + 1], int n)
{
	if (n == 3 && assign_texture_sprite(g, rc, textures, n) == t)
		return (t);
	if (rc->side == 0)
	{
		if (rc->ray_dir_x < 0)
		{
			if (g->scene.map[rc->map_x + 1][rc->map_y] == c_u)
				return (rc->texture = textures[D]->content, wall);
			else if (n == 2 && ((unsigned int)(g->scene.map[rc->map_x]
					[rc->map_y]) & d_l_u) == d_l_u)
				return (rc->texture = textures[D]->content, d_l_u);
			return (rc->texture = textures[NO]->content, wall);
		}
		else
		{
			if (g->scene.map[rc->map_x][rc->map_y] == c_u)
				return (rc->texture = textures[D]->content, wall);
			else if (n == 2 && ((unsigned int)(g->scene.map[rc->map_x]
					[rc->map_y]) & d_l_d) == d_l_d)
				return (rc->texture = textures[D]->content, d_l_d);
			return (rc->texture = textures[SO]->content, wall);
		}
	}
	return (assign_texture2(g, rc, textures, n));
}

static int	assign_texture2(t_game *g, t_raycast *rc,
				t_list *textures[D + 1], int n)
{
	{
		if (rc->ray_dir_y < 0)
		{
			if (g->scene.map[rc->map_x][rc->map_y + 1] == c_l)
				rc->texture = textures[D]->content;
			else if (n == 2 && ((unsigned int)(g->scene.map[rc->map_x]
					[rc->map_y]) & d_u_l) == d_u_l)
				return (rc->texture = textures[D]->content, d_u_l);
			else
				rc->texture = textures[WE]->content;
		}
		else
		{
			if (g->scene.map[rc->map_x][rc->map_y] == c_l)
				rc->texture = textures[D]->content;
			else if (n == 2 && ((unsigned int)(g->scene.map[rc->map_x]
					[rc->map_y]) & d_u_r) == d_u_r)
				return (rc->texture = textures[D]->content, d_u_r);
			else
				rc->texture = textures[EA]->content;
		}
	}
	return (wall);
}

#endif