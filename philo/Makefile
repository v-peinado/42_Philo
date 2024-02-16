# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpeinado <victor@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/12 15:50:56 by vpeinado          #+#    #+#              #
#    Updated: 2024/02/16 22:06:40 by vpeinado         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Program name
NAME	= philo

#Compiler
CC		= gcc
CFLAGS	= -Werror -Wextra -Wall
#CFLAGS	+= -g3 -fsanitize=thread
#CFLAGS	+= -g3 -fsanitize=address

#Includes
INC			=	-I ./includes/

#Sources
SRC_PATH	=	src/
SRC			= main.c \
				parse.c \
					utils.c \
						philo_init.c \
							philo_routine.c \
								philo_control.c 
SRCS		= $(addprefix $(SRC_PATH), $(SRC))

# Objects
OBJ_PATH = obj/
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INC)
	@echo "\033[32mPhilosophers: OK!"

clean:
	@echo "\033[33mObject files: \033[31mDeleted!"
	@rm -rf $(OBJ_PATH)

fclean: clean
	@echo "\033[33mPhilosophers: \033[31mDeleted!"
	@rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean