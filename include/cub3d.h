/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:46:50 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/01 14:23:19 by ocgraf           ###   ########.fr       */
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
# include <math.h>
# include "ft_printf.h"
# include "get_next_line.h"
# include "cub3d_struct.h"

//	libft
void		double_free(char **to_free);

//	game.c

/**
 * @brief Initialize the game structures and MLX library.
 * 
 * @param[in, out] game Pointer to the game structure to initialize.
 * @return int 1 on success, 0 on failure.
 */
int			game_init(t_game *game);

/**
 * @brief Free all allocated memory for the game.
 * 
 * @param[in] game The game structure to free.
 */
void		game_free(t_game game);

//	img_fill.c

/**
 * @brief Fill a single pixel in an image with a color.
 * 
 * @param[in] img The image to fill.
 * @param[in] x X coordinate of the pixel.
 * @param[in] y Y coordinate of the pixel.
 * @param[in] color The color value to set.
 */
void		img_fill_pixel(t_img img, int x, int y, unsigned int color);

/**
 * @brief Fill a pixel with ceiling or floor color based on Y position.
 * 
 * @param[in] game Pointer to the game structure.
 * @param[in] x X coordinate of the pixel.
 * @param[in] y Y coordinate of the pixel.
 */
void		img_fill_ceiling_floor(t_game *game, int x, int y);

/**
 * @brief Fill a pixel on the screen with texture data from raycasting.
 * 
 * @param[in] game Pointer to the game structure.
 * @param[in] x X coordinate of the pixel on screen.
 * @param[in] y Y coordinate of the pixel on screen.
 * @param[in] raycast Pointer to the raycast structure containing texture info.
 */
void		raycast_fill_img(t_game *game, int x, int y, t_raycast *raycast);

//	movement.c

/**
 * @brief Update player position and rotation based on key presses.
 * 
 * @param[in, out] game Pointer to the game structure.
 */
void		game_update_moves(t_game *game);

//	raycast.c

/**
 * @brief Main raycasting function that renders one frame.
 * 
 * @param[in, out] game Pointer to the game structure.
 */
void		raycast(t_game *game);

//	raycast_init.c

/**
 * @brief Initialize a raycast structure for a specific screen column.
 * 
 * @param[in, out] raycast Pointer to the raycast structure to initialize.
 * @param[in] game Pointer to the game structure.
 * @param[in] x Screen column index (0 to WIDTH-1).
 */
void		raycast_init(t_raycast *raycast, t_game *game, int x);

//	raycast_dda.c

/**
 * @brief DDA algorithm to find wall intersection.
 * 
 * @param[in, out] raycast Pointer to the raycast structure.
 * @param[in] game Pointer to the game structure containing the map.
 */
void		raycast_dda(t_raycast *raycast, t_game *game);

//	display_frame.c

/**
 * @brief Display callback function for the MLX loop.
 * 
 * @param[in] param Pointer to the game structure.
 * @return int 1 to continue loop, 0 to exit.
 */
int			display_frame(void *param);

//	display_minimap.c

/**
 * @brief Render the minimap overlay on the frame.
 * 
 * @param[in] game Pointer to the game structure.
 * @return int 1 on success, 0 on failure.
 */
int			display_minimap(t_game *game);

//	parsing_identify.c

/**
 * @brief Identify and parse a line from the .cub configuration file.
 * 
 * @param[in, out] line The line to parse.
 * @param[in, out] game Pointer to the game structure.
 * @return int 0 on success, 1 on error.
 */
int			identify(char *line, t_game *game);

/**
 * @brief Parse texture path identifiers (NO, SO, WE, EA).
 * 
 * @param[in] line The texture identifier line.
 * @param[in, out] game Pointer to the game structure.
 * @return int 0 on success, 1 on error.
 */
int			identify_textures(char *line, t_game *game);

/**
 * @brief Validate and process the map layout.
 * 
 * @param[in, out] map The 2D map array.
 * @param[in, out] game Pointer to the game structure.
 * @return int 0 on success, 1 on error.
 */
int			identify_map(char **map, t_game *game);

/**
 * @brief Parse color identifiers (F for floor, C for ceiling).
 * 
 * @param[in] line The color identifier line.
 * @param[in, out] game Pointer to the game structure.
 * @attention The line must start with 'F' or 'C'.
 * @return int 0 on success, 1 on error.
 */
int			identify_colors(char *line, t_game *game);

//	parsing_utils.c

/**
 * @brief Count alphanumeric characters in a string.
 * 
 * @param[in] str The string to analyze.
 * @return int Number of alphanumeric characters.
 */
int			ft_wstrlen(char *str);

/**
 * @brief Skip whitespace characters in a string.
 * 
 * @param[in] str The string to process.
 * @return char* Pointer to the first non-whitespace character.
 */
char		*skip_whitespaces(char *str);

/**
 * @brief Skip numeric digits in a string.
 * 
 * @param[in] str The string to process.
 * @return char* Pointer to the first non-digit character.
 */
char		*skip_numbers(char *str);

/**
 * @brief Remove leading whitespace from all map lines.
 * 
 * @param[in, out] game Pointer to the game structure.
 * @return int 0 on success, 1 on error.
 */
int			map_remove_whitespaces(t_game *game);

//	parsing.c

/**
 * @brief Parse the .cub configuration file and initialize game data.
 * 
 * @param[in, out] game Pointer to the game structure.
 * @param[in] argc Argument count.
 * @param[in] argv Argument values.
 * @return int 0 on success, 1 on error.
 */
int			parsing(t_game *game, int argc, char **argv);

/**
 * @brief Check if a file is readable and return its file descriptor.
 * 
 * @param[in] file_path Path to the file to check.
 * @return int File descriptor on success, -1 on error.
 */
int			readable_file(char *file_path);

/**
 * @brief Read and parse the .cub file.
 * 
 * @param[in] cub_path Path to the .cub file.
 * @param[in, out] game Pointer to the game structure.
 * @return int 0 on success, 1 on error.
 */
int			read_cub_file(char *cub_path, t_game *game);

//	t_img.c

/**
 * @brief Initialize an empty image (frame buffer).
 * 
 * @param[in] mlx_ptr Pointer to the MLX connection.
 * @param[in, out] img Pointer to the image structure to initialize.
 * @param[in] width Image width in pixels.
 * @param[in] height Image height in pixels.
 * @return int 1 on success, 0 on failure.
 */
int			t_img_init(void *mlx_ptr, t_img *img, int width, int height);

/**
 * @brief Initialize an image from an XPM file (texture).
 * 
 * @param[in] mlx_ptr Pointer to the MLX connection.
 * @param[in, out] img Pointer to the image structure to initialize.
 * @param[in] file Path to the XPM file.
 * @return int 1 on success, 0 on failure.
 */
int			t_img_init_file(void *mlx_ptr, t_img *img, char *file);

//	t_mlx.c

/**
 * @brief Check if an MLX structure is properly initialized.
 * 
 * @param[in] mlx Pointer to the MLX structure to validate.
 * @return int 1 if valid, 0 otherwise.
 */
int			t_mlx_is_valid(t_mlx *mlx);

/**
 * @brief Initialize MLX library, window, and load textures.
 * 
 * @param[in, out] mlx Pointer to the MLX structure to initialize.
 * @param[in] files Array of 4 texture file paths (NO, SO, WE, EA).
 * @return int 1 on success, 0 on failure.
 */
int			t_mlx_init(t_mlx *mlx, char *files[4]);

/**
 * @brief Free all MLX resources (window, images, display).
 * 
 * @param[in, out] mlx Pointer to the MLX structure to free.
 */
void		t_mlx_free(t_mlx *mlx);

//	hooks.c

/**
 * @brief Handle key release events.
 * 
 * @param[in] keycode The key code released.
 * @param[in, out] param Pointer to the game structure.
 * @return int 0 on success.
 */
int			key_up_hook(int keycode, void *param);

/**
 * @brief Handle key press events.
 * 
 * @param[in] keycode The key code pressed.
 * @param[in, out] param Pointer to the game structure.
 * @return int 1 on success.
 */
int			key_down_hook(int keycode, void *param);

/**
 * @brief Handle window close event.
 * 
 * @param[in] param Pointer to the MLX structure.
 * @return int Return value for MLX loop.
 */
int			close_window(void *param);

//	t_player.c

/**
 * @brief Initialize player structure based on starting position in map.
 * 
 * @param[in, out] map The game map (player character will be replaced with '0').
 * @return t_player The initialized player structure.
 */
t_player	player_init(char **map);

//textures_list.c
/**
 * @brief Add a texture file path to the game's texture list.
 * 
 * @param game Game structure pointer.
 * @param file_path Path to the texture file.
 * @param cardinal Cardinal direction identifier.
 * @return int 0 on success, 1 on error.
 */
int		add_texture(t_game *game, char *file_path);

#endif
