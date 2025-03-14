# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 12:55:36 by fmaurer           #+#    #+#              #
#    Updated: 2025/03/14 15:41:22 by jroseiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minirt

SRC_DIR		=	./src

# using the *magic* VPATH variable for finding my sources 🤯. also possible to
# use it like: `vpath %.c dir1/ dir2/ ...`. more on this ->
# https://makefiletutorial.com/#the-vpath-directive
#
# TLDR; this will make make find the correct source file `./src/exec/bla.c` for
# any obj called `obj/bla.o`
VPATH	=	./src ./src/linalg ./src/objects ./src/ui ./src/utils ./src/raytrace ./src/parsing

# list all source files here
SRCS		=	main.c \
					parse_scene.c \
					close_btn_handler.c \
					init_mrt.c \
					kbd_input_handler.c \
					rgb_to_int.c \
					vec3_new.c \
					vec3_basic_ops.c \
					vec3_products.c \
					v3_new.c \
					put_pixel_string.c \
					sidebar.c \
					objlst.c \
					print_scene.c \
					tcolr_to_int.c \
					do_stuff.c \
					tokenizer.c \
					parser.c \
					ft_isspace.c \
					ft_strndup.c

OBJDIR	=	obj
OBJS		=	$(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

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
							$(INC_DIR)/parser.h

# change this back to 'cc' @school for eval
CC			=	clang
CFLAGS	=	-g -Werror -Wall -Wextra

# special nix compilation support for mlx. see LIBMLX rule.
NIX11 = $(shell echo $$NIX11)

GRN = \033[1;32m
RED = \033[1;31m
WHT = \033[1;37m
EOC = \033[1;0m
YLW = \033[1;33m
MSGOPN = $(YLW)[[$(GRN)
MSGEND = $(YLW)]]$(EOC)

log_msg = $(MSGOPN) $(1) $(MSGEND)

# Control preproc consts in constants.h based on build host:
ifeq ($(HOST), rubi)
	BHOST = RUBI
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
	$(CC) -D$(BHOST) $(CFLAGS) $(INC) $(LIB_PATHS) -o $(NAME) $(OBJS) $(LIBS)

$(LIBFT):
	@echo -e "$(call log_msg,Compiling libft...)"
	make -C $(LIBFT_PATH) all

$(LIBMLX):
ifdef NIX11
	@echo -e "$(call log_msg,feels nixy around here.. Compiling MLX the nix way!)"
	sed -i 's/local xlib_inc="$$(get_xlib_include_path)"/local xlib_inc="$$NIX11"/g' ./minilibx-linux/configure 
	sed -i 's/mlx_int_anti_resize_win/\/\/mlx_int_anti_resize_win/g' ./minilibx-linux/mlx_new_window.c
	# sed -i 's/# define WINX 2000/# define WINX 1400/g' ./src/include/minirt.h
	# sed -i 's/# define WINY 1500/# define WINY 1000/g' ./src/include/minirt.h
	NIX11=$NIX11 make -C ./minilibx-linux/
else
	@echo -e "$(call log_msg,feels clustery around here.. compiling MLX the normal way!)"
	@echo
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
