# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/28 00:17:32 by cmenke            #+#    #+#              #
#    Updated: 2023/07/31 12:13:12 by cmenke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

SRCDIR := sources

BUILTINS := $(addprefix builtins/,echo.c \
								env.c \
								export.c \
								unset.c \
								pwd.c \
								exit.c\
								cd.c \
								export_utils.c)

CLEARING := $(addprefix clearing/,free_double_pointer.c \
									clear_structs.c)

LEXER := $(addprefix lexer/, create_tokens.c \
								syntax_error.c \
								set_token_types.c \
								split_in_sequences.c \
								expand_variables.c \
								expand_utils.c \
								redirection.c \
								token_list_to_char_array.c \
								remove_quotes.c \
								heredoc.c)

EXECUTION := $(addprefix execution/,create_processes.c \
									get_envp_cmd_paths.c \
									execute_coammand_in_child.c \
									env_list_to_char_array.c \
									duplication_of_fds_in_child.c \
									single_builtin_execution.c)

SIGNALS := $(addprefix signals/, )

SRCS := $(addprefix ${SRCDIR}/,main.c \
								${BUILTINS} \
								${LEXER} \
								${EXECUTION} \
								${SIGNALS} \
								${CLEARING} \
								helpers.c \
								shlvl.c)

OBJS := ${SRCS:.c=.o}

HEADER := includes/minishell.h includes/colors.h includes/structs.h includes/env.h

LIBFTDIR := libft

LIBFT := libft.a

#including libft and the readline library
INCLUDE := ${LIBFTDIR}/${LIBFT} -lreadline \
-I ${HOME}/goinfre/.brew/opt/readline/include/ \
-L ${HOME}/goinfre/.brew/opt/readline/lib/

CFLAGS := -Wall -Wextra -g -O0 #-fsanitize=address
##to have the same flags in libft and minishell
export CFLAGS
# CFLAGS := -Wall -Werror -Wextra

CC := cc

RM := rm -f

all: library ${NAME}

library:
	make -C ${LIBFTDIR}
	mkdir -p heredocs

${NAME}: ${OBJS} ${LIBFTDIR}/${LIBFT}
	${CC} ${CFLAGS} ${OBJS} ${INCLUDE} -o ${NAME}

${OBJS}: ${HEADER}

val:
	make && valgrind --leak-check=full ./minishell

clean:
	${RM} ${OBJS}
	make clean -C ${LIBFTDIR}

fclean: clean
	${RM} ${NAME}
	make fclean -C ${LIBFTDIR}

re: fclean all

.PHONY: all clean fclean re library

.NOTPARALLEL: