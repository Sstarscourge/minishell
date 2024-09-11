# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/19 09:32:25 by fidriss           #+#    #+#              #
#    Updated: 2024/05/09 15:48:54 by fidriss          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= $(wildcard *.c)
OBJS			= $(SRCS:.c=.o)												

CC				= cc
CFLAGS			= -Wall -Wextra -Werror
RM				= rm -rf

NAME			= lib.a

%.o:			%.c
				$(CC) $(CFLAGS) -c $< -o $@

all:			$(NAME)

$(NAME):		$(OBJS)
				ar r $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

bonus:			$(OBJS)
				ar r $(NAME) $(OBJS)

.PHONY:			all clean fclean re bonus