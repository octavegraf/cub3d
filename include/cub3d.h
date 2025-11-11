/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan-re <rchan-re@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:46:50 by rchan-re          #+#    #+#             */
/*   Updated: 2025/11/11 17:47:25 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <mlx.h>
# include <X11/keysym.h>
# include <math.h>
# include "libft.h"
# include "cub3d_struct.h"

// PARSING
int			parse(t_game *game, int argc, char **argv);

// GAME.C 
int			game_init(t_game *game);
void		game_free(t_game game);

// IMG_FILL_DISPLAY.C
void		img_fill_pixel(t_img img, int x, int y, unsigned int color);
void		img_fill_ceiling_floor(t_game *game, int x, int y);
void		raycast_fill_img(t_game *game, int x, int y, t_raycast *raycast);

// MOVEMENT.C
void		game_update_moves(t_game *game);

// RAYCAST.C
void		raycast(t_game *game);

// RAYCAST_INIT.C
void		raycast_init(t_raycast *raycast, t_game *game, int x);

// RAYCAST_DDA.C
void		raycast_dda(t_raycast *raycast, t_game *game);

// DISPLAY_FRAME.C
int			display_frame(void *param);

// DISPLAY_MINIMAP.C
int			display_minimap(t_game *game);

//T_IMG.C
int			t_img_init(void *mlx_ptr, t_img *img, int width, int height);
int			t_img_init_file(void *mlx_ptr, t_img *img, char *file);

// T_MLX.C
int			t_mlx_is_valid(t_mlx *mlx);
int			t_mlx_init(t_mlx *mlx, char *files[4]);
void		t_mlx_free(t_mlx *mlx);

// HOOKS.C
int			key_up_hook(int keycode, void *param);
int			key_down_hook(int keycode, void *param);
int			close_window(void *param);

// T_PLAYER.C
t_player	player_init(char **map);

#endif
