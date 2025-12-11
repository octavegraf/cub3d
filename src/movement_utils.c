/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:01:16 by ocgraf            #+#    #+#             */
/*   Updated: 2025/12/11 17:00:46 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef BONUS

int	is_available(t_game *game, double jump_x, double jump_y)
{
	int	try_x;
	int	try_y;

	try_x = game->player.pos_x + jump_x;
	try_y = game->player.pos_y + jump_y;
	if (jump_x < 0)
	{
		//if (game->scene.map[try_x][((int)(game->player.pos_y))] == c_l
		//	&& (int)try_y == (int)(game->player.pos_y))
		//	return (1);
		if (game->scene.map[(int)(game->player.pos_x)][try_y] == c_u
			&& game->scene.map[try_x][try_y] != c_u)
			return (0);
		if (ft_strchr(AVAILABLE_X_NEG, game->scene.map[try_x][try_y]) != NULL)
			return (1);
		return (0);
	}
	else if (jump_x > 0)
	{
		if (game->scene.map[(int)(game->player.pos_x)][try_y] != c_u
			&& game->scene.map[try_x][try_y] == c_u)
			return (0);
		else if (ft_strchr(AVAILABLE_X_POS, game->scene.map[try_x][try_y]) != NULL)
			return (1);
		return (0);
	}
	else if (jump_y < 0)
	{
		if (game->scene.map[try_x][(int)(game->player.pos_y)] == c_l
			&& game->scene.map[try_x][try_y] != c_l)
			return (0);
/*		if (game->scene.map[try_x][((int)(game->player.pos_y))] == c_l
			&& (int)try_y == (int)(game->player.pos_y))
			return (1);
		else if (game->scene.map[try_x][((int)(game->player.pos_y))] == c_l
			&& (int)try_y < (int)(game->player.pos_y))
			return (0);*/
		else if (ft_strchr(AVAILABLE_Y_NEG, game->scene.map[try_x][try_y]) != NULL)
			return (1);
		return (0);
	}
	else if (jump_y > 0)
	{
		if (game->scene.map[try_x][(int)(game->player.pos_y)] != c_l
			&& game->scene.map[try_x][try_y] == c_l)
			return (0);
		else if (ft_strchr(AVAILABLE_Y_POS, game->scene.map[try_x][try_y]) != NULL)
			return (1);
		return (0);
	}
	return (0);
}

#else

int	is_available(t_game *game, double jump_x, double jump_y)
{
	int	try_x;
	int	try_y;

	try_x = game->player.pos_x + jump_x;
	try_y = game->player.pos_y + jump_y;
	if (game->scene.map[try_x][try_y] == '0')
		return (1);
	return (0);
}

#endif

int	check_jump(double jump)
{
	if (jump > 1 || jump < -1)
		return (0);
	return (1);
}
