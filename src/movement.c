/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan-re <rchan-re@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:43:24 by rchan-re          #+#    #+#             */
/*   Updated: 2025/11/11 17:43:24 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	game_move(t_game *g, double move_dir, double mv_plane)
{
	if (move_dir != 0)
	{
		if (g->scene.map[(int)(g->player.pos_x
				+ 2 * g->player.dir_x * move_dir)]
				[(int)(g->player.pos_y)] == '0')
			g->player.pos_x += g->player.dir_x * move_dir;
		if (g->scene.map[(int)(g->player.pos_x)]
				[(int)(g->player.pos_y
				+ 2 * g->player.dir_y * move_dir)] == '0')
			g->player.pos_y += g->player.dir_y * move_dir;
	}
	if (mv_plane != 0)
	{
		if (g->scene.map[(int)(g->player.pos_x
				+ 2 * g->player.plane_x * mv_plane)]
				[(int)(g->player.pos_y)] == '0')
			g->player.pos_x += g->player.plane_x * mv_plane;
		if (g->scene.map[(int)(g->player.pos_x)]
				[(int)(g->player.pos_y
				+ 2 * g->player.plane_y * mv_plane)] == '0')
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
