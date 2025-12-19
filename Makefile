CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -MMD
NAME				=	cub3d
FILES				=	add_texture assign_texture close_window display_frame display_minimap doors enum_strchr game_free game_init img_fill key_down_hook key_up_hook main minimap_draw_doors minimap_draw_player_fov minimap_free minimap_get minimap_set_params mouse movement movement_utils parsing parsing_identify parsing_identify_map parsing_identify_map_extra parsing_replace_char quadri_fill_minimap parsing_utils quadri_get_x quadri_get_y raycast raycast_dda raycast_init raycast_compute raycast_get_texture timeval t_img t_mlx_free t_mlx_init t_player t_scene_free
SRC					=	$(addprefix src/, $(addsuffix .c, $(FILES)))
INCLUDES			=	-Ift_printf -Imlx -Ignl -Iinclude
OBJ_FOLDER			=	objects/
OBJ					=	$(addprefix $(OBJ_FOLDER), $(SRC:.c=.o))
OBJ_BONUS			=	$(addprefix $(OBJ_FOLDER), $(SRC:.c=_bonus.o))
DPD					=	$(addprefix $(OBJ_FOLDER), $(SRC:.c=.d))
DPD_BONUS			=	$(addprefix $(OBJ_FOLDER), $(SRC:.c=_bonus.d))

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LIBS = -L$(MLX_FOLDER) -L/usr/X11/lib -framework OpenGL -framework AppKit -lX11 -lXext $(MLX) $(FT_PRINTF) $(GNL)
else
	LIBS = -L$(FT_PRINTF_FOLDER) -L$(MLX_FOLDER) -lX11 -lXext -lm -lftprintf -lmlx $(GNL)
endif

FT_PRINTF_FOLDER	=	ft_printf/
FT_PRINTF			=	$(addprefix $(FT_PRINTF_FOLDER), libftprintf.a)

MLX_FOLDER			=	mlx/
MLX					=	$(addprefix $(MLX_FOLDER), libmlx.a)

GNL_FOLDER			=	gnl/
GNL					=	$(addprefix $(GNL_FOLDER), get_next_line.a)

all					:	$(NAME)

$(NAME)				:	$(OBJ) $(FT_PRINTF) $(MLX) $(GNL)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

$(OBJ_FOLDER)%.o	:	%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_FOLDER)%_bonus.o	: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

-include $(DPD) $(DPD_BONUS)

$(FT_PRINTF):
	make -C $(FT_PRINTF_FOLDER) all

$(MLX):
	make -C $(MLX_FOLDER) all

$(GNL):
	make -C $(GNL_FOLDER) all

$(NAME)_bonus		:	$(OBJ_BONUS)  $(FT_PRINTF) $(MLX) $(GNL)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME)_bonus $(LIBS)
bonus				:	CFLAGS += -DBONUS
bonus				:	$(NAME)_bonus
b					:	bonus

clean				:
	rm -rf $(OBJ_FOLDER)
	make -C $(FT_PRINTF_FOLDER) clean
	make -C $(MLX_FOLDER) clean
	make -C $(GNL_FOLDER) clean

fclean				:	clean
	rm -rf $(NAME) $(NAME)_bonus
	make -C $(FT_PRINTF_FOLDER) fclean
	make -C $(GNL_FOLDER) fclean

re					:	fclean all

debug				:
	make -C $(FT_PRINTF_FOLDER) debug
debug				:	CFLAGS += -g3
debug				:	re



fsanitize			:	CFLAGS += -fsanitize=address
fsanitize			:	debug

.PHONY				:	all clean fclean re debug fsanitize bonus
.DELETE_ON_ERROR	:
#.SILENT				:
