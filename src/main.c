/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:43:24 by rchan-re          #+#    #+#             */
/*   Updated: 2025/11/22 10:55:00 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	game = (t_game){0};
	if (parsing(&game, argc, argv))
		return (game_free(game), 1);
	if (game_init(&game) == 0)
		return (1);
	mlx_hook(game.mlx.win_ptr, 2, 1L << 0, &key_down_hook, &game);
	mlx_hook(game.mlx.win_ptr, 3, 1L << 1, &key_up_hook, &game);
	mlx_hook(game.mlx.win_ptr, 17, 0, &close_window, &(game.mlx));
	mlx_loop_hook(game.mlx.mlx_ptr, &display_frame, &game);
	mlx_loop(game.mlx.mlx_ptr);
	game_free(game);
	return (0);
}
