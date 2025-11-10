CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -MMD
NAME				=	cub3d
SRC					=	$(addsuffix .c, files)
INCLUDES			=	-Ilibft -Imlx
OBJ_FOLDER			=	objects/
OBJ					=	$(addprefix $(OBJ_FOLDER), $(SRC:.c=.o))
DPD					=	$(addprefix $(OBJ_FOLDER), $(SRC:.c=.d))

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LIBS = -L$(MLX_FOLDER) -framework OpenGL -L/usr/X11/lib -framework AppKit
else
	LIBS = -L$(LIBFT_FOLDER) -L$(MLX_FOLDER) -lX11 -lXext -lm -lft -lmlx
endif

LIBFT_FOLDER		=	libft/
LIBFT				=	$(addprefix $(LIBFT_FOLDER), libft.a)

MLX_FOLDER			=	mlx/
MLX					=	$(addprefix $(MLX_FOLDER), libmlx.a)

all					:	$(LIBFT) $(MLX) $(NAME)

$(NAME)				:	$(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

$(OBJ_FOLDER)%.o	: %.c
	mkdir -p $(OBJ_FOLDER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

-include $(DPD)

$(LIBFT):
	make -C $(LIBFT_FOLDER) all

$(MLX):
	make -C $(MLX_FOLDER) all

clean				:
	rm -rf $(OBJ_FOLDER)
	make -C $(LIBFT_FOLDER) clean
	make -C $(MLX_FOLDER) clean

fclean				:	clean
	rm -rf $(NAME)
	make -C $(LIBFT_FOLDER) fclean

re					:	fclean all

debug				:	CFLAGS += -g3
debug				:	re
	make -C $(LIBFT_FOLDER) debug

fsanitize			:	CFLAGS += -fsanitize=address
fsanitize			:	debug

.PHONY				:	all clean fclean re debug fsanitize
.DELETE_ON_ERROR	:
#.SILENT				: