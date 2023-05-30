NAME = cub3d

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g

RM = rm -f

LIBFT = ./libft

LIBFT_LIB = ./libft/libft.a

MLX_LIB = ./minilibx_opengl_20191021/libmlx.a

SR_PATH = ./srcs/

OBJ_PATH = ./obj/

INC_PATH = ./includes/

SR =	main.c \
			gopars.c \
			get_next_line.c \
			get_next_line_utils.c \
			draw.c \
			draw2.c \
			draw3.c \
			window.c \
			help_window.c \
			help_window2.c \
			intersection.c \
			mini_map.c \
			manage_rays.c \
			utils.c \
		
SRC = $(addprefix $(SR_PATH), $(SR))

OBJ = $(addprefix $(OBJ_PATH), $(SR:.c=.o))

all: $(NAME)

${OBJ_PATH}%.o : ${SR_PATH}%.c
	@mkdir -p ${OBJ_PATH}
	cc ${CFLAGS} -I ${INC_PATH} -c $< -o $@

$(NAME): $(OBJ)
	make -C $(LIBFT)
	make -C ./minilibx_opengl_20191021
	cc $(CFLAGS) -I $(INC_PATH) -lmlx -framework OpenGL -framework AppKit $(OBJ) $(LIBFT_LIB) $(MLX_LIB) -o $(NAME)

clean:
	make clean -C $(LIBFT)
	make clean -C ./minilibx_opengl_20191021
	$(RM) $(OBJ)
	$(RM) -r $(OBJ_PATH)

fclean: clean
	make fclean -C $(LIBFT)
	$(RM) $(NAME)

re: fclean all