/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:46:50 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/11 15:32:30 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCT_H
# define CUB3D_STRUCT_H

# define MOVE 0.08
# define ROTATE 0.08
# define MOUSE_SENSITIVITY 0.3
# define FREQ_SEC 0
# define FREQ_USEC 100000

# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_H 104
# define KEY_M  109
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# ifdef __linux__
#  define KEY_ESC 65307
#  define KEY_SPACE 32
#  define LEFT_CLICK 1

# elif __APPLE__
#  define KEY_ESC 53
#  define KEY_SPACE 49
#  define LEFT_CLICK 1
# endif

# ifdef BONUS
#  define MAP_ELEMENTS "10NSEWD"
#  define RADIUS_MAP 3
#  define MIN_DIM_RATIO 0.2
#  define SIZE_PLAYER 1
#  define MINIMAP_FOV_STEP 0.01

#  define MINIMAP_WHITE "0MVYIO."

enum e_door
{
	c_l = 'L',
	c_u = 'U',
	o_l = 'M',
	o_u = 'V',
	d_u_l = 'Y',
	d_u_r = 'I',
	d_l_u = 'O',
	d_l_d = '.'
};

# else
#  define MAP_ELEMENTS "10NSEW"
# endif

enum e_screensize
{
	WIDTH = 1920,
	HEIGHT = 1080
};

enum e_color
{
	RED = 16711680,
	GREEN = 65280,
	BLUE = 255,
	WHITE = 16777215,
	BLACK = 0
};

enum e_direction
{
	NO,
	SO,
	WE,
	EA,
	D,
	F,
	C,
};

# ifdef BONUS

enum e_key_press
{
	ARROW_LEFT,
	ARROW_RIGHT,
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	MINIMAP_HIDE,
	MINIMAP_MAXIMIZE
};
# else

enum e_key_press
{
	ARROW_LEFT,
	ARROW_RIGHT,
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
};
# endif

typedef struct s_quadri
{
	int	x_start;
	int	x_end;
	int	y_start;
	int	y_end;
	int	color;
}	t_quadri;

enum e_mouse_move
{
	MOUSE_LEFT,
	MOUSE_RIGHT
};

/**
 * @brief Structure for the scene.
 * 
 * @param textures Array of texture file paths (North, South, West, East).
 * @param floor_color Color of the floor.
 * @param ceiling_color Color of the ceiling.
 * @param map 2D array representing the map layout.
 */
# ifdef BONUS

typedef struct s_scene
{
	t_list	*textures[D + 1];
	int		floor_color;
	int		ceiling_color;
	char	**map;
	char	**minimap;
	int		minimap_radius_screen;
	int		minimap_scale_screen_map;
	int		minimap_radius_map;
}	t_scene;
# else

typedef struct s_scene
{
	t_list	*textures[7];
	int		floor_color;
	int		ceiling_color;
	char	**map;
}	t_scene;
# endif

/**
 * @brief Structure for the player.
 * 
 * @param pos_x Player's X position in the world.
 * @param pos_y Player's Y position in the world.
 * @param dir_x X component of the direction vector.
 * @param dir_y Y component of the direction vector.
 * @param plane_x X component of the camera plane vector.
 * @param plane_y Y component of the camera plane vector.
 */
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

/**
 * @brief Structure for an image.
 * 
 * @param mlx_ptr Pointer to the MLX connection.
 * @param img_ptr Pointer to the MLX image.
 * @param w Image width in pixels.
 * @param h Image height in pixels.
 * @param buf Pointer to the image buffer data.
 * @param bpp Bits per pixel.
 * @param size_line Size of one line in bytes.
 * @param endian Endianness (0 for little endian, 1 for big endian).
 */
typedef struct s_img
{
	void	*mlx_ptr;
	void	*img_ptr;
	int		w;
	int		h;
	char	*buf;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

/**
 * @brief Structure for the MLX library elements.
 * 
 * @param mlx_ptr Pointer to the MLX connection.
 * @param win_ptr Pointer to the MLX window.
 * @param frame The main frame buffer image.
 * @param textures Array of 4 texture images (North, South, West, East).
 */
typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	frame;
	t_list	*textures[D + 1];
	int		mouse_x;
	int		mouse_y;
}	t_mlx;

/**
 * @brief Main game structure.
 * 
 * @param mlx MLX library elements.
 * @param player Player data.
 * @param scene Scene data (map, textures, colors).
 * @param key_press Array of key states for movement and rotation.
 */

# ifdef BONUS

typedef struct s_game
{
	t_mlx			mlx;
	t_player		player;
	t_scene			scene;
	char			key_press[8];
	float			mouse_move[2];
	struct timeval	tv;
	int				minimap_radius_screen;
	int				minimap_scale_screen_map;
}	t_game;
# else

typedef struct s_game
{
	t_mlx			mlx;
	t_player		player;
	t_scene			scene;
	char			key_press[6];
}	t_game;

# endif

/**
 * @brief Structure for raycasting calculations.
 * 
 * @param draw_start Starting Y position to draw wall.
 * @param draw_end Ending Y position to draw wall.
 * @param color Wall color.
 * @param camera_x Camera X position in screen space.
 * @param ray_dir_x Ray direction X component.
 * @param ray_dir_y Ray direction Y component.
 * @param map_x Current map X coordinate.
 * @param map_y Current map Y coordinate.
 * @param side_dist_x Distance to next vertical grid line.
 * @param side_dist_y Distance to next horizontal grid line.
 * @param delta_dist_x Distance between vertical grid lines.
 * @param delta_dist_y Distance between horizontal grid lines.
 * @param step_x Direction to step in X (-1 or 1).
 * @param step_y Direction to step in Y (-1 or 1).
 * @param side Which side was hit (0 for vertical, 1 for horizontal).
 * @param wall_x Exact X coordinate on wall.
 * @param tex_x Texture X coordinate.
 * @param tex_y Texture Y coordinate.
 * @param tex_pos Current texture position.
 * @param texture Pointer to the texture image.
 * @param step Step for texture Y coordinate.
 */
typedef struct s_raycast
{
	int				draw_start;
	int				draw_end;
	unsigned int	color;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				step_x;
	int				step_y;
	int				side;
	double			wall_x;
	int				tex_x;
	int				tex_y;
	double			tex_pos;
	t_img			*texture;
	double			step;
}	t_raycast;

# define ERR_USAGE "Error\nUse program with one map.\n"
# define ERR_NULL_PATH "Error\nnull path\n"
# define ERR_OPEN_FILE "Error\nopen file: %s \n"
# define ERR_WRONG_LINE "Error\nWrong line\n"
# define ERR_UNKNOWN_ID "Error\nUnknown identifier\n"
# define ERR_TEXTURE_NOT_READABLE "Error\nTexture file not readable\n"
# define ERR_TEXTURE_NOT_XPM "Error\nTexture file not .xpm\n"
# define ERR_COLOR_OUT_OF_RANGE "Error\nColor value out of range\n"
# define ERR_UNKNOWN_COLOR_ID "Error\nUnknown color identifier\n"
# define ERR_INVALID_MAP_CHAR "Error\nInvalid map character or not closed.\n"
# define ERR_INVALID_PLAYER_COUNT "Error\nInvalid number of player\n"
# define ERR_MAP_OPEN "Error\nMap open %d,%d \n"
# define ERR_MLX_INIT "Error\nmlx_init()\n"
# define ERR_MLX_NEW_WINDOW "Error\nmlx_new_window()\n"
# define ERR_MLX_NEW_IMAGE "Error\nmlx_new_image()\n"
# define ERR_MLX_GET_DATA_ADDR "Error\nmlx_get_data_addr()\n"
# define ERR_MLX_XPM_FILE "Error\nmlx_xpm_file_to_image()\n"
# define ERR_CUB_EXTENSION "Error\n.cub file extension required\n"
# define ERR_INVALID_CARDINAL "Error\nInvalid cardinal direction\n"
# define ERR_GETTIMEOFDAY "Error\ngettimeofday()\n"
# define ERR_MALLOC "Error\nmalloc()\n"
# define ERR_MINIMAP_PLAYER "Error\nMinimap: invalid player size\n"
# define ERR_MINIMAP_SIZE "Error\nMinimap: invalid minimap dimensions\n"
# define ERR_FREQ_ANIMATION "Error\nAnimation: invalid update frequence\n"
# define ERR_DOOR_MISS_WALLS "Error\nMissing texture or walls around a door\n"

#endif
