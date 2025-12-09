/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:43:24 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/08 13:14:15 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (ft_dprintf(2, ERR_USAGE), 1);
	game = (t_game){0};
	game.scene.ceiling_color = -1;
	game.scene.floor_color = -1;
	if (gettimeofday(&(game.tv), NULL) != 0)
		return (ft_dprintf(2, ERR_GETTIMEOFDAY), 1);
	if (read_cub_file(argv[1], &game, 0))
		return (game_free(&game), 1);
	if (game_init(&game) == 0)
		return (1);
	mlx_hook(game.mlx.win_ptr, 2, 1L << 0, &key_down_hook, &game);
	mlx_hook(game.mlx.win_ptr, 3, 1L << 1, &key_up_hook, &game);
	mlx_hook(game.mlx.win_ptr, 17, 0, &close_window, &(game.mlx));
	mlx_loop_hook(game.mlx.mlx_ptr, &display_frame, &game);
	mlx_loop(game.mlx.mlx_ptr);
	game_free(&game);
	return (0);
}
