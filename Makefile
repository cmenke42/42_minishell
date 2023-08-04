# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/01 23:48:03 by cmenke            #+#    #+#              #
#    Updated: 2023/08/04 11:25:30 by wmoughar         ###   ########.fr        #
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
								export_utils.c\
								export_utils2.c)

CLEARING := $(addprefix clearing/,free_double_pointer.c \
									clear_structs.c)

LEXER := $(addprefix lexer/,tokenize_command_line.c \
							tokenize_command_line_helpers.c \
								syntax_error.c \
								set_token_types.c \
								split_in_sequences.c \
								redirection.c \
								token_list_to_char_array.c \
								remove_quotes.c)

EXECUTION := $(addprefix execution/,create_processes.c \
									get_envp_cmd_paths.c \
									execute_coammand_in_child.c \
									env_list_to_char_array.c \
									duplication_of_fds_in_child.c \
									single_builtin_execution.c \
									invoke_close_functions.c)

SIGNALS := $(addprefix signals/, set_signals_functions.c \
								signal_handlers.c)

VARIABLE_EXPANSION := $(addprefix variable_expansion/, variable_expansion.c \
														variable_expansion_get_name_value.c \
														variable_expansion_trim_value.c \
														variable_expansion_utils.c)

HEREDOC := $(addprefix heredoc/, heredoc.c \
									heredoc_file_creation_deletion.c \
									heredoc_helpers.c)

SRCS := $(addprefix ${SRCDIR}/,main.c \
								${BUILTINS} \
								${LEXER} \
								${EXECUTION} \
								${SIGNALS} \
								${CLEARING} \
								${VARIABLE_EXPANSION} \
								${HEREDOC} \
								helpers.c \
								print_error.c)

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
	$(RM) -r heredocs

re: fclean all

.PHONY: all clean fclean re library

.NOTPARALLEL: