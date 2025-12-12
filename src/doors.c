/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:50:01 by ocgraf            #+#    #+#             */
/*   Updated: 2025/12/12 18:50:24 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "cub3d.h"

static void	check_current_left(char **map, int x, int y)
{
	if (map[x][y] == c_l)
	{
		map[x][y] = o_l;
		map[x - 1][y] = d_l_u;
		map[x + 1][y] = d_l_d;
	}
	else if (map[x][y] == o_l)
	{
		map[x][y] = c_l;
		map[x - 1][y] = '1';
		map[x + 1][y] = '1';
	}
}

static void	check_right_left(char **map, int x, int y)
{
	if (map[x][y + 1] == c_l)
	{
		map[x][y + 1] = o_l;
		map[x - 1][y + 1] = d_l_u;
		map[x + 1][y + 1] = d_l_d;
	}
	else if (map[x][y + 1] == o_l)
	{
		map[x][y + 1] = c_l;
		map[x - 1][y + 1] = '1';
		map[x + 1][y + 1] = '1';
	}
}

static void	check_current_up(char **map, int x, int y)
{
	if (map[x][y] == c_u)
	{
		map[x][y] = o_u;
		map[x][y - 1] = d_u_l;
		map[x][y + 1] = d_u_r;
	}
	else if (map[x][y] == o_u)
	{
		map[x][y] = c_u;
		map[x][y - 1] = '1';
		map[x][y + 1] = '1';
	}
}

static void	check_below_up(char **map, int x, int y)
{
	if (map[x + 1][y] == c_u)
	{
		map[x + 1][y] = o_u;
		map[x + 1][y - 1] = d_u_l;
		map[x + 1][y + 1] = d_u_r;
	}
	else if (map[x + 1][y] == o_u)
	{
		map[x + 1][y] = c_u;
		map[x + 1][y - 1] = '1';
		map[x + 1][y + 1] = '1';
	}
}

void	door_hook(t_game *game)
{
	check_current_left(game->scene.map, game->player.pos_x, game->player.pos_y);
	check_right_left(game->scene.map, game->player.pos_x, game->player.pos_y);
	check_current_up(game->scene.map, game->player.pos_x, game->player.pos_y);
	check_below_up(game->scene.map, game->player.pos_x, game->player.pos_y);
}

#endif
