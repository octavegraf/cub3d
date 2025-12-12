/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_get_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan-re <rchan-re@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:08:32 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/12 14:45:17 by rchan-re         ###   ########.fr       */
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

static int	assign_texture(t_game *game, t_raycast *raycast, t_list *textures[D + 1], int n)
{
	if (raycast->side == 0)
	{
		if (raycast->ray_dir_x < 0)
		{
			// door up closed, from below
			if (game->scene.map[raycast->map_x + 1][raycast->map_y] == c_u)
				raycast->texture = textures[D]->content;
			// door left open, up door
			else if (n == 2 && game->scene.map[raycast->map_x][raycast->map_y] == d_l_u)
				return (raycast->texture = textures[D]->content, d_l_u);
			else
				raycast->texture = textures[NO]->content;
		}
		else
		{
			// door up closed, from above
			if (game->scene.map[raycast->map_x][raycast->map_y] == c_u)
				raycast->texture = textures[D]->content;
			// door left open, down door
			else if (n == 2 && game->scene.map[raycast->map_x][raycast->map_y] == d_l_d)
				return (raycast->texture = textures[D]->content, d_l_d);
			else
				raycast->texture = textures[SO]->content;
		}
	}
	else
	{
		if (raycast->ray_dir_y < 0)
		{
			// door left closed, from the right
			if (game->scene.map[raycast->map_x][raycast->map_y + 1] == c_l)
				raycast->texture = textures[D]->content;
			// door up open, left door
			else if (n == 2 && game->scene.map[raycast->map_x][raycast->map_y] == d_u_l)
				return (raycast->texture = textures[D]->content, d_u_l);
			else
				raycast->texture = textures[WE]->content;
		}
		else
		{
			// door left closed, from the left
			if (game->scene.map[raycast->map_x][raycast->map_y] == c_l)
				raycast->texture = textures[D]->content;
			// door up open, right door
			else if (n == 2 && game->scene.map[raycast->map_x][raycast->map_y] == d_u_r)
				return (raycast->texture = textures[D]->content, d_u_r);
			else
				raycast->texture = textures[EA]->content;
		}
	}
	return ('1');
}

int	raycast_get_texture(t_game *game, t_raycast *raycast, struct timeval *tv, int n)
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
