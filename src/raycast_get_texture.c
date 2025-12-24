/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_get_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:08:32 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/24 15:04:57 by rchan-re         ###   ########.fr       */
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
