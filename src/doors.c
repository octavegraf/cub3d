/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:50:01 by ocgraf            #+#    #+#             */
/*   Updated: 2025/12/15 22:59:51 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "cub3d.h"

void	door_hook_2(t_game *game, int x, int y);
void	door_hook_3(t_game *game, int x, int y);

void	door_hook(t_game *game)
{
	int	x;
	int	y;

	x = game->player.pos_x;
	y = game->player.pos_y;
	if (game->scene.map[x][y] == c_l)
	{
		game->scene.map[x][y] = o_l;
		game->scene.map[x - 1][y] |= d_l_u;
		game->scene.map[x + 1][y] |= d_l_d;
	}
	else if (game->scene.map[x][y + 1] == c_l)
	{
		game->scene.map[x][y + 1] = o_l;
		game->scene.map[x - 1][y + 1] |= d_l_u;
		game->scene.map[x + 1][y + 1] |= d_l_d;
	}
	else if (game->scene.map[x][y] == c_u)
	{
		game->scene.map[x][y] = o_u;
		game->scene.map[x][y - 1] |= d_u_l;
		game->scene.map[x][y + 1] |= d_u_r;
	}
	else
		door_hook_2(game, x, y);
}

void	door_hook_2(t_game *game, int x, int y)
{
	if (game->scene.map[x + 1][y] == c_u)
	{
		game->scene.map[x + 1][y] = o_u;
		game->scene.map[x + 1][y - 1] |= d_u_l;
		game->scene.map[x + 1][y + 1] |= d_u_r;
	}
	else if (game->scene.map[x][y] == o_l)
	{
		game->scene.map[x][y] = c_l;
		game->scene.map[x - 1][y] ^= d_l_u;
		game->scene.map[x + 1][y] ^= d_l_d;
	}
	else if (game->scene.map[x][y + 1] == o_l)
	{
		game->scene.map[x][y + 1] = c_l;
		game->scene.map[x - 1][y + 1] ^= d_l_u;
		game->scene.map[x + 1][y + 1] ^= d_l_d;
	}
	else
		door_hook_3(game, x, y);
}

void	door_hook_3(t_game *game, int x, int y)
{
	if (game->scene.map[x][y] == o_u)
	{
		game->scene.map[x][y] = c_u;
		game->scene.map[x][y - 1] ^= d_u_l;
		game->scene.map[x][y + 1] ^= d_u_r;
	}
	else if (game->scene.map[x + 1][y] == o_u)
	{
		game->scene.map[x + 1][y] = c_u;
		game->scene.map[x + 1][y - 1] ^= d_u_l;
		game->scene.map[x + 1][y + 1] ^= d_u_r;
	}
}

#endif
