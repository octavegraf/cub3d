/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan-re <rchan-re@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:43:24 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/02 17:50:53 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	raycast_update_texture(t_img **texture, t_list **node_img, struct timeval *tv)
{
	*texture = (*node_img)->content;
	if (UPDATE_TEXTURE((long long)tv->tv_sec) != 0)
		*node_img = (*node_img)->next;
	return (1);
}

static int	raycast_get_texture(t_game *game, t_raycast *raycast, struct timeval *tv)
{
	static t_list	*texture_no = NULL;
	static t_list	*texture_so = NULL;
	static t_list	*texture_ea = NULL;
	static t_list	*texture_we = NULL;

	if (texture_no == NULL)
		texture_no = game->mlx.textures[NO];
	if (texture_so == NULL)
		texture_so = game->mlx.textures[SO];
	if (texture_ea == NULL)
		texture_ea = game->mlx.textures[EA];
	if (texture_we == NULL)
		texture_we = game->mlx.textures[WE];
	if (raycast->side == 0)
	{
		if (raycast->ray_dir_x < 0)
			return (raycast_update_texture(&(raycast->texture), &texture_no, tv));
		else
			return (raycast_update_texture(&(raycast->texture), &texture_so, tv));
	}
	else
	{
		if (raycast->ray_dir_y < 0)
			return (raycast_update_texture(&(raycast->texture), &texture_we, tv));
		else
			return (raycast_update_texture(&(raycast->texture), &texture_ea, tv));
	}
}

static void	raycast_compute_texture(t_game *g, t_raycast *rc, double d, int lh)
{
	if (rc->side == 0)
		rc->wall_x = g->player.pos_y + d * rc->ray_dir_y;
	else
		rc->wall_x = g->player.pos_x + d * rc->ray_dir_x;
	rc->wall_x -= floor((rc->wall_x));
	rc->tex_x = rc->wall_x * (double)rc->texture->w;
	if (rc->side == 0 && rc->ray_dir_x > 0)
		rc->tex_x = rc->texture->w - rc->tex_x - 1;
	if (rc->side == 1 && rc->ray_dir_y < 0)
		rc->tex_x = rc->texture->w - rc->tex_x - 1;
	rc->step = 1.0 * rc->texture->h / lh;
	rc->tex_pos = (rc->draw_start - HEIGHT / 2 + lh / 2) * rc->step;
}

static int	raycast_compute(int x, t_game *game, t_raycast *rc, struct timeval *tv)
{
	double		perp_wall_dist;
	int			line_height;

	raycast_init(rc, game, x);
	raycast_dda(rc, game);
	if (rc->side == 0)
		perp_wall_dist = (rc->side_dist_x - rc->delta_dist_x);
	else
		perp_wall_dist = (rc->side_dist_y - rc->delta_dist_y);
	line_height = HEIGHT / perp_wall_dist;
	rc->draw_start = -line_height / 2 + HEIGHT / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = line_height / 2 + HEIGHT / 2;
	if (rc->draw_end >= HEIGHT)
		rc->draw_end = HEIGHT - 1;
	if (raycast_get_texture(game, rc, tv) == 0)
		return (0);
	raycast_compute_texture(game, rc, perp_wall_dist, line_height);
	return (1);
}

int	raycast(t_game *game)
{
	int				x;
	int				y;
	t_raycast		raycast;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (ft_dprintf(2, ERR_GETTIMEOFDAY), 0);
	game_update_moves(game);
	x = 0;
	while (x < WIDTH)
	{
		if (raycast_compute(x, game, &raycast, &tv) == 0)
			return (0);
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
