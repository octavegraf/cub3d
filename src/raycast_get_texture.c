/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_get_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan-re <rchan-re@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:08:32 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/11 13:48:41 by rchan-re         ###   ########.fr       */
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

static void	assign_texture(t_game *game, t_raycast *raycast, t_list *textures[D + 1])
{
//	static int	i = 0;

	/*// update i
	if ()*/
	if (raycast->side == 0)
	{
		if (raycast->ray_dir_x < 0)
		{
			// door up closed, from below
			if (game->scene.map[raycast->map_x + 1][raycast->map_y] == c_u)
				raycast->texture = textures[D]->content;
			else
				raycast->texture = textures[NO]->content;
		}
		else
		{
			// door up closed, from above
			if (game->scene.map[raycast->map_x][raycast->map_y] == c_u)
				raycast->texture = textures[D]->content;
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
			else
				raycast->texture = textures[WE]->content;
		}
		else
		{
			if (game->scene.map[raycast->map_x][raycast->map_y] == c_l)
				raycast->texture = textures[D]->content;
			else
				raycast->texture = textures[EA]->content;
		}
	}

}

void	raycast_get_texture(t_game *game, t_raycast *raycast,
		struct timeval *tv)
{
	static t_list	*textures[D + 1] = {0};
	int				i;

	i = 0;
	while (i < D + 1) // ??
	{
		update_texture(&(textures[i]), game->mlx.textures[i], &(game->tv), tv);
		i++;
	}
	if (diff_time_tv(&(game->tv), tv) != 0)
		update_time_tv(&(game->tv), FREQ_SEC, FREQ_USEC);
	assign_texture(game, raycast, textures);
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
