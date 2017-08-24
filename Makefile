# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbichero <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/25 10:03:12 by bbichero          #+#    #+#              #
#    Updated: 2017/08/19 13:30:22 by bbichero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_minishell

# LIBFT
LFTPATH = libft/
LFTIPATH = -I $(LFTPATH)
LFT = -L $(LFTPATH) -lft

OBJPATH = obj
SRCPATH = .
INCLUDE = -I ./

# MLX
CC = gcc

LIBS = $(LFT)
INCLUDES = $(INCLUDE) $(LFTIPATH)

BASEFLAGS = -Wall -Wextra # -Wconversion
CURSEFLAGS = -lcurses
CFLAGS = $(BASEFLAGS) -Werror -O2 -g 

LFTCALL = all
LFTRE = re

SRCSFILES = main.c \
	ft_env.c \
	get_next_line.c \
	ft_built_in.c \
	ft_handle_cmd.c \
	free.c \
	ft_init.c \
	utils.c \
	ft_handle_line.c \
	signal.c \
	termios.c 

SRC = $(addprefix $(SRCPATH)/,$(SRCSFILES))
OBJECTS = $(SRC:$(SRCPATH)/%.c=$(OBJPATH)/%.o)

RM = rm -rf

Y = \033[0;33m
R = \033[0;31m
G = \033[0;32m
E = \033[39m

all: l $(NAME)

$(NAME): $(OBJECTS)
	@echo "$(Y)[COMPILING MINISHELL] $(G) $(CC) -o $@ $(CFLAGS) -g $(OBJECTS) $(INCLUDES) $(LIBS) $(E)"
	@$(CC) -o $@ $(CFLAGS) $(OBJECTS) $(INCLUDES) $(LIBS) $(CURSEFLAGS)
	@echo "$(Y)[COMPILING NMINISHELL DONE]$(E)"

$(OBJECTS): $(OBJPATH)/%.o : $(SRCPATH)/%.c
	@mkdir -p $(dir $@)
	@$(CC) -o $@ $(CFLAGS) $(INCLUDES) -c $<

clean:
	@$(RM) $(OBJPATH)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(LFTPATH)

l:
	@echo "$(Y)[COMPILING LIBFT] $(G) cd $(LFTPATH) && $(MAKE) $(E)"
	@cd $(LFTPATH) && $(MAKE)
	@echo "$(Y)[COMPILING LIBFT DONE]$(E)"

re: fclean all
