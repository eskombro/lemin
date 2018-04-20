# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhigelin <dhigelin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 17:25:17 by sjimenez          #+#    #+#              #
#    Updated: 2018/04/11 16:13:56 by dhigelin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
NAME_V = visu

FLAGS = -Wall -Werror -Wextra

SRCS_DIR = srcs/
SRCS_V_DIR = lemin_visu/srcs/

LIBS_PATH=$(shell echo ~/.libssj)
BREW_PATH=$(shell echo ~/.brew)

INCLUDES = includes/
INCLUDES_V = includes/
LIBFT_INCLUDES = libft/includes

LIB = libft -lft
LIB_V = -lSDL2 -lSDL2_image -lSDL2_ttf

SRCS =	main.c					\
		move_ants.c				\
		parsing.c				\
		parsing2.c				\
		paths.c					\

SRCS_O = $(addprefix $(SRCS_DIR),  $(SRCS:.c=.o))

SRCS_V =	main.c				\
			parsing.c			\
			parsing2.c			\
			sdl_basics.c		\
			drawing.c			\
			texts.c				\
			map_graphic_loop.c	\
			ants.c				\

SRCS_O_V = $(addprefix $(SRCS_V_DIR),  $(SRCS_V:.c=.o))

ifeq ("$(FLAG)", "SHOW_ALL")
REDIR =
else ifeq ("$(FLAG)", "SHOW_ERROR")
REDIR = 1>/dev/null
else
REDIR = 1>/dev/null 2>/dev/null
endif

ifeq ("$(FLAG2)", "SANITIZE")
SANITIZE = -fsanitize=address -g3
else
SANITIZE =
endif

all: lib $(NAME)

lib:
ifeq ("$(wildcard $(LIBS_PATH)/lib/libSDL2.dylib)","")
	@echo " \033[0;32m\n------ Compiling SDL --------------\033[0;0m"
	@export DYLD_LIBRARY_PATH=$(LIBS_PATH)/lib && cd lemin_visu/SDL2 && ./configure --prefix=$(LIBS_PATH) $(REDIR) && make $(REDIR) && make install $(REDIR)
	@install_name_tool -id $(LIBS_PATH)/lib/libSDL2.dylib $(LIBS_PATH)/lib/libSDL2.dylib
	@echo "SDL compiled"
endif
ifeq ("$(wildcard $(LIBS_PATH)/lib/libSDL2_image.dylib)","")
	@echo " \033[0;32m\n------ Compiling SDL_image --------\033[0;0m"
	@export DYLD_LIBRARY_PATH=$(LIBS_PATH)/lib && cd lemin_visu/SDL2_image && ./configure --prefix=$(LIBS_PATH) $(REDIR) && make $(REDIR) && make install $(REDIR)
	@install_name_tool -id $(LIBS_PATH)/lib/libSDL2_image.dylib $(LIBS_PATH)/lib/libSDL2_image.dylib
	@install_name_tool -change /usr/local/lib/libSDL2-2.0.0.dylib $(LIBS_PATH)/lib/libSDL2.dylib $(LIBS_PATH)/lib/libSDL2_image.dylib
	@echo "SDL_Image compiled"
endif
ifeq ("$(wildcard $(BREW_PATH)/Cellar/freetype)","")
	@brew install FreeType $(REDIR)
endif
ifeq ("$(wildcard $(LIBS_PATH)/lib/libSDL2_ttf.dylib)","")
	@echo " \033[0;32m\n------ Compiling SDL_ttf --------\033[0;0m"
	@export DYLD_LIBRARY_PATH=$(LIBS_PATH)/lib && cd lemin_visu/SDL2_ttf && ./configure --prefix=$(LIBS_PATH) $(REDIR) && make $(REDIR) && make install $(REDIR)
	@install_name_tool -id $(LIBS_PATH)/lib/libSDL2_ttf.dylib $(LIBS_PATH)/lib/libSDL2_ttf.dylib
	@install_name_tool -change /usr/local/lib/libSDL2-2.0.0.dylib $(LIBS_PATH)/lib/libSDL2.dylib $(LIBS_PATH)/lib/libSDL2_image.dylib
	@echo "SDL_ttf compiled"
endif

%.o: %.c
	@gcc -c $(FLAGS) -o $@ $< -I $(INCLUDES) -I $(LIBFT_INCLUDES) -I lemin_visu/includes -I $(LIBS_PATH)/include $(SANITIZE)

$(NAME): $(SRCS_O) $(SRCS_O_V)
	@echo " \033[0;32m\n------ Compiling Libft ------------\033[0;0m"
	@make -C libft
	@echo " \033[0;32m\n------ Compiling sources ----------\033[0;0m"
	@gcc $(FLAGS) -o $(NAME) $(SRCS_O) -I $(LIBFT_INCLUDES) -L $(LIB) -I $(INCLUDES) $(SANITIZE)
	@echo "Sources compiled"
	@echo " \033[0;32m\n------ Lem-in project compiled ----\033[0;0m"
	@echo "lem-in created"
	@echo " \033[0;32m\n------ Compiling visual  ----------\033[0;0m"
	@gcc $(FLAGS) -o $(NAME_V) $(SRCS_O_V) -L $(LIB) -I $(INCLUDES_V) -I $(LIBFT_INCLUDES) $(LIB_V) -L $(LIBS_PATH)/lib  $(SANITIZE)
	@echo "visu created"

clean:
	@echo " \033[0;32m\n------ Lem-in clean ---------------\033[0;0m"
	@rm -Rf $(SRCS_O) $(SRCS_O_V)
	@make -C libft clean
	@echo "Lem-in clean executed"

fclean: clean
	@echo " \033[0;32m\n------ Lem-in fclean --------------\033[0;0m"
	@rm -Rf $(NAME) $(NAME_V)
	@make -C libft fclean
	@echo "Lem-in fclean executed"

clean_libs:
	@rm -Rf $(LIBS_PATH)

re: fclean all

.PHONY: re clean fclean all

.NOTPARALLEL:
