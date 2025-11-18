CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -MMD
NAME				=	cub3d
FILES				=	display_frame display_minimap game hooks img_fill init_scene main movement raycast raycast_dda raycast_init t_img t_mlx t_player
SRC					=	$(addprefix src/, $(addsuffix .c, $(FILES)))
INCLUDES			=	-Ift_printf -Imlx -Ignl -Iinclude
OBJ_FOLDER			=	objects/
OBJ					=	$(addprefix $(OBJ_FOLDER), $(SRC:.c=.o))
DPD					=	$(addprefix $(OBJ_FOLDER), $(SRC:.c=.d))

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LIBS = -L$(MLX_FOLDER) -framework OpenGL -L/usr/X11/lib -framework AppKit
else
	LIBS = -L$(FT_PRINTF_FOLDER) -L$(MLX_FOLDER) -L$(GNL_FOLDER) -lX11 -lXext -lm -lftprintf -lmlx -lgnl
endif

FT_PRINTF_FOLDER	=	ft_printf/
FT_PRINTF			=	$(addprefix $(FT_PRINTF_FOLDER), libftprintf.a)

MLX_FOLDER			=	mlx/
MLX					=	$(addprefix $(MLX_FOLDER), libmlx.a)

GNL_FOLDER			=	gnl/
GNL					=	$(addprefix $(GNL_FOLDER), get_next_line.a)

all					:	$(FT_PRINTF) $(MLX) $(GNL) $(NAME)

$(NAME)				:	$(OBJ) $(FT_PRINTF) $(MLX) $(GNL)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

$(OBJ_FOLDER)%.o	: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

-include $(DPD)

$(FT_PRINTF):
	make -C $(FT_PRINTF_FOLDER) all

$(MLX):
	make -C $(MLX_FOLDER) all

$(GNL):
	make -C $(GNL_FOLDER) all

clean				:
	rm -rf $(OBJ_FOLDER)
	make -C $(FT_PRINTF_FOLDER) clean
	make -C $(MLX_FOLDER) clean
	make -C $(GNL_FOLDER) clean

fclean				:	clean
	rm -rf $(NAME)
	make -C $(FT_PRINTF_FOLDER) fclean
	make -C $(GNL_FOLDER) fclean

re					:	fclean all

debug				:
	make -C $(FT_PRINTF_FOLDER) debug
debug				:	CFLAGS += -g3
debug				:	re



fsanitize			:	CFLAGS += -fsanitize=address
fsanitize			:	debug

.PHONY				:	all clean fclean re debug fsanitize
.DELETE_ON_ERROR	:
#.SILENT				: