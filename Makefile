# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/14 17:02:20 by fmaurer           #+#    #+#              #
#    Updated: 2025/04/19 01:10:10 by fmaurer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minirt

SRC_DIR		=	./src

# using the *magic* VPATH variable for finding my sources 🤯. also possible to
# use it like: `vpath %.c dir1/ dir2/ ...`. more on this ->
# https://makefiletutorial.com/#the-vpath-directive
#
# TLDR; this will make make find the correct source file `./src/exec/bla.c` for
# any ob called `ob/bla.o`
VPATH	=	./src ./src/linalg ./src/objects ./src/ui ./src/utils ./src/raytrace \
				./src/parsing ./src/xpm ./src/setup_scene

# list all source files here
SRCS		=	main.c \
					close_btn_handler.c \
					init_mrt.c \
					kbd_input_handler.c \
					kbd_handle_fov_sub.c \
					rgb_to_int_tcolr.c \
					vec3_new.c \
					vec3_basic_ops.c \
					vec3_products.c \
					v3_new.c \
					v3_basic_ops.c \
					v3_advanced_ops.c \
					mtrx_ops.c \
					mtrx_new_print.c \
					get_rotmtrx.c \
					put_pixel_string.c \
					sidebar.c \
					sidebar_print_text.c \
					ui-utils.c \
					objlst.c \
					objlst_print.c \
					print_scene.c \
					tcolr_to_int.c \
					raytrace.c \
					math_utils.c \
					get_object_colr.c \
					intersect_ray_obj.c \
					sphere.c \
					calculate_lights.c \
					colr_utils.c \
					do_stuff.c \
					general_utils.c \
					ft_atof.c \
					par_handle_objs.c \
					par_alight_cam.c \
					par_scene.c \
					par_parse_coord_key.c \
					par_objs.c \
					par_objs2.c \
					par_lineparse.c \
					par_utils.c \
					par_utils2.c \
					par_validator.c \
					par_validate_colr_vector.c \
					tokenizer.c \
					tokenizer_nums.c \
					setup_scene.c \
					raytrace_xpm.c \
					xpm.c \
					cleanup_mrt.c \
					kbd_cam.c \
					cam_get_new_pos_rot.c \
					circle.c \
					kbd_other.c \
					triangle.c \
					colr_base_utils.c

OBJDIR	=	obj
OBJS		=	$(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

# X11 MAC
#X11_FIX_PATH = ~/x11_include_fix
X11_PATH = $(shell brew --prefix libx11)
XORG_PATH = $(shell brew --prefix xorgproto)
XEXT_PATH = $(shell brew --prefix libxext)

LIBFT_PATH	= ./libft
LIBFT				= $(LIBFT_PATH)/libft.a

LIBMLX_PATH = ./minilibx-linux
LIBMLX 			= ./minilibx-linux/libmlx.a

LIB_PATHS = -L$(LIBMLX_PATH) -L$(LIBFT_PATH)
LIBS 			= -lmlx -lXext -lX11 -lm -lft

INC_DIR			= $(SRC_DIR)/include
INC					= -I$(INC_DIR) -I$(LIBMLX_PATH) -I$(LIBFT_PATH)

MINRT_HDRS	= $(INC_DIR)/minirt.h \
							$(INC_DIR)/vec3.h \
							$(INC_DIR)/v3.h \
							$(INC_DIR)/constants.h \
							$(INC_DIR)/objects.h \
							$(INC_DIR)/mtrx.h \
							$(INC_DIR)/parsing.h \
							$(INC_DIR)/keycodes.h

# FIXME: change this back to 'cc' @school for eval
CC			=	clang
CFLAGS	=	-g -Werror -Wall -Wextra
# -I$(X11_PATH)/include -I$(XORG_PATH)/include -I$(XEXT_PATH)/include -Wno-deprecated-non-prototype
#LDFLAGS += -L$(X11_PATH)/lib -L$(XEXT_PATH)/lib -lX11 -lXext

# special nix compilation support for mlx. see LIBMLX rule.
NIX11 = $(shell echo $$NIX11)

GRN = \033[38;5;40m
RED = \033[1;31m
WHT = \033[1;37m
EOC = \033[1;0m
YLW = \033[38;5;3m
MSGOPN = $(YLW)[[$(GRN)
MSGEND = $(YLW)]]$(EOC)

log_msg = $(MSGOPN) $(1) $(MSGEND)

# Control preproc consts in constants.h based on build host:

HOST = $(shell hostname)
ifeq ($(findstring rubi,$(HOST)), rubi)
	BHOST = RUBI
else ifeq ($(findstring wolfsburg,$(HOST)), wolfsburg)
	BHOST = SCHOOL
else
	BHOST = DEFAULT
endif

all: $(NAME)

$(OBJDIR)/%.o : %.c $(MINRT_HDRS)
	@mkdir -p $(OBJDIR)
	@echo -e "$(call log_msg,Compiling: $<)"
	@$(CC) -D$(BHOST) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(LIBMLX) $(MINRT_HDRS)
	@echo -e "$(call log_msg,Compiling minirt...)"
	@echo -e "$(call log_msg,For host $(HOST)!)"
	$(CC) -D$(BHOST) $(CFLAGS) $(INC) $(LIB_PATHS) -o $(NAME) $(OBJS) $(LDFLAGS) $(LIBS)

$(LIBFT):
	@echo -e "$(call log_msg,Compiling libft...)"
	make -C $(LIBFT_PATH) all

$(LIBMLX):
ifeq ($(shell uname), Darwin)
	@echo -e "$(call log_msg,Compiling MLX for macOS...)"
	make -C ./minilibx-linux/
endif
ifeq ($(NIX11),)
	@echo -e "$(call log_msg,Compiling MLX the normal way!)"
	make -C ./minilibx-linux/
else
	echo "NIX11 = $(NIX11)"
	@echo -e "$(call log_msg,Compiling MLX the Nix way!)"
	sed -i 's/local xlib_inc="$$(get_xlib_include_path)"/local xlib_inc="$$NIX11"/g' ./minilibx-linux/configure
	sed -i 's/mlx_int_anti_resize_win/\/\/mlx_int_anti_resize_win/g' ./minilibx-linux/mlx_new_window.c
	make -C ./minilibx-linux/
endif

bonus: $(NAME)

mlx: $(LIBMLX)

debug: $(SRCS) $(LIBFT) $(LIBMLX) $(MINRT_HDRS)
	$(CC) -g $(CFLAGS) $(INC) $(LIB_PATHS) -o $(NAME) $(SRCS) $(LIBS)

setup:
	@echo -e "$(call log_msg,Setting things up...)"
	@rm -rf ./minilibx-linux ./test_maps
	@echo -e "$(call log_msg,Downloading mlx...)"
	@wget -c https://cdn.intra.42.fr/document/document/31543/minilibx-linux.tgz 2> /dev/null
	@wget -c https://cdn.intra.42.fr/document/document/31544/minilibx_opengl.tgz 2> /dev/null
	@echo	-e "$(call log_msg,Unpacking mlx...)"
	@tar xzf ./minilibx-linux.tgz > /dev/null
	@tar xzf ./minilibx_opengl.tgz > /dev/null
	@echo	-e "$(call log_msg,Cloning libft submodule...)"
	@git submodule update --init
	@sleep 1s
	@echo -e "$(call log_msg,There you go!)"

fullclean:
	@echo -e "$(call log_msg,Removing libft objs.)"
	@make -s -C $(LIBFT_PATH) clean
	@echo -e "$(call log_msg,Removing libmlx objs.)"
	@make -s -C $(LIBMLX_PATH) clean
	@echo -e "$(call log_msg,Removing minirt objs.)"
	@rm -rf $(OBJDIR)

clean:
	@echo -e "$(call log_msg,Removing minirt objs.)"
	@rm -rf $(OBJDIR)

fullfclean:
	@echo -e "$(call log_msg,fcleaning libft.)"
	@make -s -C $(LIBFT_PATH) fclean
	@echo -e "$(call log_msg,fcleaning libmlx.)"
	@make -s -C $(LIBMLX_PATH) clean
	@echo -e "$(call log_msg,Removing minirt objs.)"
	@rm -rf $(OBJDIR)
	@echo -e "$(call log_msg,Removing $(NAME) binary.)"
	@rm -f $(NAME)

fclean: clean
	@echo -e "$(call log_msg,Removing $(NAME) binary.)"
	@rm -f $(NAME)

fullre: fullfclean all

re: fclean all

.PHONY: all fullclean clean fclean re mlx debug bonus setup help
