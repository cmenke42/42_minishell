/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 00:10:38 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/12 11:52:54 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//custom
# include "../libft/libft.h"
# include "colors.h"
# include "env.h"

# include <stdio.h>
//readline
# include <readline/readline.h>
# include <readline/history.h>

//tc functions
# include <termios.h>

//signals
# include <signal.h>

// //terminal
// # include <sys/ttydefaults.h>

# include <stdbool.h>

//open
# include <fcntl.h>

//Wait functions
# include <sys/types.h>
# include <sys/wait.h>

# define PROMPT "Minishell:$ "
# define SQUOTE_ERROR "minishell: syntax error while looking for matching `''"
# define DQUOTE_ERROR "minishell: syntax error while looking for matching `\"'"

typedef struct s_shell_data
{
	char	*command_line_read;
	bool	add_line_to_history;
	char	**envp;
	t_list	*command_sequences;
}				t_shell_data;

typedef struct s_command_sequences
{
	t_list	*tokens;
	char	*command_path;
	char	**args;
	int		input_fd;
	int		output_fd;
}				t_command_sequences;

typedef struct s_tokens
{
	char	*token;
	char	type;
}				t_tokens;

// enum e_token_type
// {
// 	/* data */
// };

//main
//lexer
	//create_tokens.c
bool	ft_process_command_line(t_shell_data *shell_data);
bool	ft_create_command_sequence(char *command_line_read, t_list **command_sequences);
bool	ft_create_tokens_for_sequence(char *command_line_read, t_list **command_sequences);
void	ft_skip_to_next_non_delimiter(char **command_line);
bool	ft_find_next_token(char **string, char **start, t_list **tokens, bool *pipe);
void	ft_skip_quote_block(char **string);
void	ft_move_while_same_char(char **command_line, char c);
bool	ft_create_one_token(char *start, char *end, t_list **token);
	// syntax_error.c
bool	ft_check_equal_quote_amt(char *s);
// clearing
	//ft_free_double_pointer.c
void	ft_free_double_pointer_char(char ***ptr);
void	ft_free_double_pointer_int(int ***ptr);
	// clear_all.c
void	ft_clear_token(void *token);
void	ft_clear_command_sequence(void *sequence);
// void	ft_free_command_sequences(void *command_sequences);
//helpers.c
	// void ft_print_list(t_list *list);

#endif