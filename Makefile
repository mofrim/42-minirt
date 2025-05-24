# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/14 17:02:20 by fmaurer           #+#    #+#              #
#    Updated: 2025/05/24 10:07:30 by fmaurer          ###   ########.fr        #
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
					init_mrt_scene.c \
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
					mtrx_transp_det.c \
					mtrx_new_print.c \
					get_rotmtrx.c \
					put_pixel_string.c \
					sidebar.c \
					sidebar_print_text.c \
					get_float_string.c \
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
					launch_ui.c \
					general_utils.c \
					error_utils.c \
					ft_atof.c \
					par_handle_objs.c \
					par_alight_cam.c \
					par_scene.c \
					par_parse_coord_key.c \
					par_objs_3d.c \
					par_objs_2d.c \
					par_lineparse.c \
					par_utils.c \
					read_scenefile.c \
					parse_colr.c \
					parse_v3.c \
					tokenizer.c \
					parse_number_token.c \
					setup_scene.c \
					raytrace_xpm.c \
					xpm.c \
					cleanup_mrt.c \
					kbd_cam.c \
					cam_get_new_pos_rot.c \
					circle.c \
					kbd_other.c \
					triangle.c \
					colr_base_utils.c \
					export_ppm.c \
					hyper.c \
					hyper_mtrx_normal.c \
					hyper_get_colr.c \
					hyper_boloid_intersect.c \
					objlst_print_funcs.c \
					parse_texture.c \
					show_xpm.c \
					read_tex_nmap.c \
					sphere_get_scolr.c \
					sphere_get_normal.c \
					cylinder_body.c \
					cylinder_caps.c \
					cylinder_color.c \
					cylinder_intersect.c \
					cylinder_normal.c \
					plane.c \
					sphere_bump.c \
					raytrace_hq.c \
					canvas2viewport_traceray.c \
					kbd_handle_hq.c \
					plane_get_scolr.c

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
ECHO = echo -e
ifeq ($(findstring rubi,$(HOST)), rubi)
	BHOST = RUBI
else ifeq ($(findstring wolfsburg,$(HOST)), wolfsburg)
	BHOST = SCHOOL
	ECHO = echo
else
	BHOST = DEFAULT
endif

all: $(NAME)

$(OBJDIR)/%.o : %.c $(MINRT_HDRS)
	@mkdir -p $(OBJDIR)
	@$(ECHO) "$(call log_msg,Compiling: $<)"
	@$(CC) -D$(BHOST) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(LIBMLX) $(MINRT_HDRS)
	@$(ECHO) "$(call log_msg,Compiling minirt...)"
	@$(ECHO) "$(call log_msg,For host $(HOST)!)"
	$(CC) -D$(BHOST) $(CFLAGS) $(INC) $(LIB_PATHS) -o $(NAME) $(OBJS) $(LDFLAGS) $(LIBS)

$(LIBFT):
	@$(ECHO) "$(call log_msg,Compiling libft...)"
	make -C $(LIBFT_PATH)

$(LIBMLX):
ifeq ($(shell uname), Darwin)
	@$(ECHO) "$(call log_msg,Compiling MLX for macOS...)"
	make -C ./minilibx-linux/
endif
ifeq ($(NIX11),)
	@$(ECHO) "$(call log_msg,Compiling MLX the normal way!)"
	make -C ./minilibx-linux/
else
	echo "NIX11 = $(NIX11)"
	@$(ECHO) "$(call log_msg,Compiling MLX the Nix way!)"
	sed -i 's/local xlib_inc="$$(get_xlib_include_path)"/local xlib_inc="$$NIX11"/g' ./minilibx-linux/configure
	sed -i 's/mlx_int_anti_resize_win/\/\/mlx_int_anti_resize_win/g' ./minilibx-linux/mlx_new_window.c
	make -C ./minilibx-linux/
endif

# multithreaded raytracing as a bonus-bonus...
THREADS = $(shell cat /proc/cpuinfo | grep processor | wc -l)
BONUS_SRC = ./src/raytrace/raytrace_pthread_bonus.c \
						./src/raytrace/raytrace_thread_funcs_bonus.c \
						./src/raytrace/raytrace_hq_bonus.c
bonus: $(SRCS) $(BONUS_SRC)
	$(ECHO) "$(call log_msg,Compiling the multithreading bonus ^^)"
	$(CC) -D$(BHOST) -DTHREADS=$(THREADS) -DBONUS $(CFLAGS) $(INC) $(LIB_PATHS) -o $(NAME) $^ $(LDFLAGS) $(LIBS) -pthread

mlx: $(LIBMLX)

debug: $(SRCS) $(LIBFT) $(LIBMLX) $(MINRT_HDRS)
	$(CC) -g $(CFLAGS) $(INC) $(LIB_PATHS) -o $(NAME) $(SRCS) $(LIBS)

setup:
	@$(ECHO) "$(call log_msg,Setting things up...)"
	@rm -rf ./minilibx-linux ./test_maps
	@$(ECHO) "$(call log_msg,Downloading mlx...)"
	@wget -c https://cdn.intra.42.fr/document/document/34406/minilibx-linux.tgz 2> /dev/null
	@wget -c https://cdn.intra.42.fr/document/document/34407/minilibx_macos_opengl.tgz 2> /dev/null
	@echo	-e "$(call log_msg,Unpacking mlx...)"
	@tar xzf ./minilibx-linux.tgz > /dev/null
	@tar xzf ./minilibx_macos_opengl.tgz > /dev/null
	@echo	-e "$(call log_msg,Cloning libft submodule...)"
	@git submodule update --init
	@sleep 1s
	@$(ECHO) "$(call log_msg,There you go!)"

fullclean:
	@$(ECHO) "$(call log_msg,Removing libft objs.)"
	@make -s -C $(LIBFT_PATH) clean
	@$(ECHO) "$(call log_msg,Removing libmlx objs.)"
	@make -s -C $(LIBMLX_PATH) clean
	@$(ECHO) "$(call log_msg,Removing minirt objs.)"
	@rm -rf $(OBJDIR)

clean:
	@$(ECHO) "$(call log_msg,Removing minirt objs.)"
	@rm -rf $(OBJDIR)

fullfclean:
	@$(ECHO) "$(call log_msg,fcleaning libft.)"
	@make -s -C $(LIBFT_PATH) fclean
	@$(ECHO) "$(call log_msg,fcleaning libmlx.)"
	@make -s -C $(LIBMLX_PATH) clean
	@$(ECHO) "$(call log_msg,Removing minirt objs.)"
	@rm -rf $(OBJDIR)
	@$(ECHO) "$(call log_msg,Removing $(NAME) binary.)"
	@rm -f $(NAME)

fclean: clean
	@$(ECHO) "$(call log_msg,Removing $(NAME) binary.)"
	@rm -f $(NAME)

fullre: fullfclean all

fullbear: fullfclean
	@bear -- make

re: fclean all

.PHONY: all fullclean clean fclean re mlx debug bonus setup help fullbear
