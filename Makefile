# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/29 13:15:51 by abenchel          #+#    #+#              #
#    Updated: 2024/10/14 20:58:00 by fidriss          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
XFLAGS = -I /goinfre/fidriss/homebrew/opt/readline/include

NAME = minishell
SRCS = ./exec/execution.c ./exec/exec_pipeline2.c ./exec/handle_heredoc.c ./exec/redirections.c \
		./exec/utils.c ./exec/utils6.c ./exec/builtins/execute.c ./exec/builtins/mini_cd.c ./exec/builtins/mini_echo.c \
		./exec/builtins/mini_env.c ./exec/builtins/mini_export.c ./exec/builtins/mini_pwd.c \
		 ./exec/builtins/mini_unset.c ./exec/builtins/mini_exit.c ./libft/funct_libft.c \
		./libft/funct_libft2.c ./libft/funct_libft3.c ./libft/funct_libft4.c ./libft/funct_libft5.c \
		./libft/funct_libft6.c ./error/check_error.c ./libft/elem_funct.c ./lexer/lexer.c ./lexer/lexer2.c ./lexer/mainlexer.c ./parsing/parsing.c \
		./parsing/parsing2.c ./parsing/mainpars.c expand/expand.c minishell.c ./exec/utils2.c ./exec/utils3.c \
		./error/check_error2.c expand/expand2.c expand/expand3.c ./exec/signals.c ./exec/exec_pipeline.c ./exec/utils4.c \
		./exec/utils5.c ./exec/exec_pipeline3.c ./exec/utils7.c ./exec/utils8.c ./exec/find_path.c ./exec/find_executable.c \
		
OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -L/goinfre/fidriss/homebrew/opt/readline/lib  $(OBJS)  -o $(NAME) -lreadline  $(XFLAGS)


%.o:  %.c minishell.h
	$(CC) $(CFLAGS) $(XFLAGS) -c  $< -o $@  
clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
