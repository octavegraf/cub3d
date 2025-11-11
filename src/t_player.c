/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_player.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan-re <rchan-re@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:43:24 by rchan-re          #+#    #+#             */
/*   Updated: 2025/11/11 17:43:24 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	player_fill_dir(t_player *player, double dir_x, double dir_y)
{
	player->dir_x = dir_x;
	player->dir_y = dir_y;
}

static void	player_fill_plane(t_player *player, double plane_x, double plane_y)
{
	player->plane_x = plane_x;
	player->plane_y = plane_y;
}

static void	player_fill_attributes(t_player *player, int i, int j, char c)
{
	player->pos_x = i + 0.5;
	player->pos_y = j + 0.5;
	if (c == 'N')
	{
		player_fill_dir(player, -1.0, 0.0);
		player_fill_plane(player, 0.0, 0.66);
	}
	else if (c == 'S')
	{
		player_fill_dir(player, 1.0, 0.0);
		player_fill_plane(player, 0.0, -0.66);
	}
	else if (c == 'E')
	{
		player_fill_dir(player, 0.0, 1.0);
		player_fill_plane(player, 0.66, 0.0);
	}
	else if (c == 'W')
	{
		player_fill_dir(player, 0.0, -1.0);
		player_fill_plane(player, -0.66, 0.0);
	}
}

t_player	player_init(char **map)
{
	t_player	player;
	char		c;
	int			i;
	int			j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			c = map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				player_fill_attributes(&player, i, j, c);
				map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	return (player);
}
