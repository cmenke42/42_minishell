# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/28 00:17:32 by cmenke            #+#    #+#              #
#    Updated: 2023/07/10 17:47:33 by cmenke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

SRCDIR := sources

BUILTINS := $(addprefix builtins/,utils.c \
								 echo.c \
								 env.c \
								 export.c \
								 export_utils.c \
								 unset.c \
								 pwd.c \
								 exit.c)

CLEARING := $(addprefix clearing/,free_double_pointer.c \
									clear_all.c)

LEXER := $(addprefix lexer/, create_tokens.c)

# EXECUTION := $(addprefix execution/,get_envp_cmd_paths.c \
# 									fork_childs.c)

SIGNALS := $(addprefix signals/, )

SRCS := $(addprefix ${SRCDIR}/,main.c \
								${BUILTINS} \
								${LEXER} \
								${EXECUTION} \
								${SIGNALS} \
								${CLEARING})

OBJS := ${SRCS:.c=.o}

HEADER := includes/minishell.h includes/colors.h

LIBFTDIR := libft

LIBFT := libft.a

HOME := /Users/cmenke

#including libft and the readline library
INCLUDE := ${LIBFTDIR}/${LIBFT} -lreadline \
-I ${HOME}/goinfre/.brew/opt/readline/include/ \
-L ${HOME}/goinfre/.brew/opt/readline/lib/

CFLAGS := -Wall -Wextra -g #-fsanitize=address
# CFLAGS := -Wall -Werror -Wextra

CC := cc

RM := rm -f

all: library ${NAME}

library:
	make -C ${LIBFTDIR}

${NAME}: ${OBJS} ${LIBFTDIR}/${LIBFT}
	${CC} ${CFLAGS} ${OBJS} ${INCLUDE} -o ${NAME}

${OBJS}: ${HEADER}

clean:
	${RM} ${OBJS}
	make clean -C ${LIBFTDIR}

fclean: clean
	${RM} ${NAME}
	make fclean -C ${LIBFTDIR}

re: fclean all

.PHONY: all clean fclean re library

.NOTPARALLEL: