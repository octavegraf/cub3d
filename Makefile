CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror
NAME				=	cub3d
SRC					=	$(addsuffix .c, files)
INCLUDES			=	-Ilibft -Imlx
LINUX				=	-lX11 -lXext -lm
MACOS				=	-L$(MLX_FOLDER) -framework OpenGL -L/usr/X11/lib -framework AppKit
OBJ_FOLDER			=	objects/
OBJ					=	$(addprefix $(OBJ_FOLDER), $(SRC:.cpp =.o))

LIBFT				=	libft.a
LIBFT_FOLDER		=	libft/

MLX					=	libmlx.a
MLX_FOLDER			=	mlx/

all					:	$(LIBFT) $(MLX) $(NAME)

$(NAME)				: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_FOLDER)%.o	: %.cpp
	@mkdir -p $(OBJ_FOLDER)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_FOLDER) all --no-print-directory

$(MLX):
	@make -C $(MLX_FOLDER) all --no-print-directory > /dev/null

clean				:
	@rm -rf $(OBJ_FOLDER)
	@make -C $(LIBFT_FOLDER) clean --no-print-directory
	@make -C $(MLX_FOLDER) clean --no-print-directory > /dev/null

fclean				:	clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_FOLDER) fclean --no-print-directory

re					:	fclean all

debug				:	CFLAGS += -g3
debug				:	re
debug				:	@make -C $(LIBFT_FOLDER) debug --no-print-directory

fsanitize			:	CFLAGS += -fsanitize=address
fsanitize			:	debug

.PHONY				:	all clean fclean re debug fsanitize
.DELETE_ON_ERROR	:
.SILENT				: