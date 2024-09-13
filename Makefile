# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/09 15:51:34 by fidriss           #+#    #+#              #
#    Updated: 2024/09/13 11:07:26 by fidriss          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = execution.c execution2.c handle_heredoc.c redirections.c utils.c
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I/goinfre/fidriss/homebrew/opt/readline/include
LDFLAGS = -L/goinfre/fidriss/homebrew/opt/readline/lib -lreadline

LIBDIR = lib
LIB = $(LIBDIR)/lib.a

RM = rm -rf

all: $(LIB) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIB) $(LDFLAGS) -o $(NAME)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): 
	$(MAKE) -C $(LIBDIR)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBDIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBDIR) fclean		

re: fclean all

.PHONY: all clean fclean re
