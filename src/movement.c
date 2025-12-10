/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan-re <rchan-re@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:43:24 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/10 11:45:00 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_jump(double jump)
{
	if (jump > 1 || jump < -1)
		return (0);
	return (1);
}

static int	is_available(char **map, int i, int j)
{
	if (map[i][j] == '0')
		return (1);
	return (0);
}

static void	game_move(t_game *g, double move_dir, double mv_plane)
{
	if (check_jump(2 * g->player.dir_x * move_dir) == 1)
	{
		if (is_available(g->scene.map, g->player.pos_x + 2 * g->player.dir_x
				* move_dir, g->player.pos_y))
			g->player.pos_x += g->player.dir_x * move_dir;
	}
	if (check_jump(2 * g->player.dir_y * move_dir) == 1)
	{
		if (is_available(g->scene.map, g->player.pos_x, g->player.pos_y
				+ 2 * g->player.dir_y * move_dir))
			g->player.pos_y += g->player.dir_y * move_dir;
	}
	if (check_jump(2 * g->player.plane_x * mv_plane) == 1)
	{
		if (is_available(g->scene.map, g->player.pos_x + 2 * g->player.plane_x
				* mv_plane, g->player.pos_y))
			g->player.pos_x += g->player.plane_x * mv_plane;
	}
	if (check_jump(2 * g->player.plane_y * mv_plane) == 1)
	{
		if (is_available(g->scene.map, g->player.pos_x, g->player.pos_y
				+ 2 * g->player.plane_y * mv_plane))
			g->player.pos_y += g->player.plane_y * mv_plane;
	}
}

static void	game_rotate(t_game *game, double rotate)
{
	double	old_x;

	old_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(-rotate)
		- game->player.dir_y * sin(-rotate);
	game->player.dir_y = old_x * sin(-rotate)
		+ game->player.dir_y * cos(-rotate);
	old_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(-rotate)
		- game->player.plane_y * sin(-rotate);
	game->player.plane_y = old_x * sin(-rotate)
		+ game->player.plane_y * cos(-rotate);
}

void	game_update_moves(t_game *game)
{
	if (game->key_press[MOVE_UP] == 1)
		game_move(game, MOVE, 0);
	if (game->key_press[MOVE_DOWN] == 1)
		game_move(game, -MOVE, 0);
	if (game->key_press[MOVE_RIGHT] == 1)
		game_move(game, 0, MOVE);
	if (game->key_press[MOVE_LEFT] == 1)
		game_move(game, 0, -MOVE);
	if (game->key_press[ARROW_RIGHT] == 1)
		game_rotate(game, ROTATE);
	if (game->key_press[ARROW_LEFT] == 1)
		game_rotate(game, -ROTATE);
}
