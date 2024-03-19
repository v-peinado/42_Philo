# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpeinado <vpeinado@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/12 15:50:56 by vpeinado          #+#    #+#              #
#    Updated: 2024/03/19 18:44:45 by vpeinado         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Program name
NAME	= philo

#Compiler
CC		= gcc
CFLAGS	= -Werror -Wextra -Wall
#CFLAGS	+= -g3 -fsanitize=thread
CFLAGS	+= -g3 -fsanitize=address
RM		= rm -f

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

obj:
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INC)
	@echo "\033[1;32mPhilosophers: OK!\033[0;0m"

clean:
	@echo "\033[1;33mObject files: \033[31mDeleted!\033[0;0m"
	@$(RM) -Rf $(OBJ_PATH)

fclean: clean
	@echo "\033[1;33mPhilosophers: \033[31mDeleted!\033[0;0m"
	@$(RM) -f $(NAME)

re: fclean all

.PHONY: all re clean fclean