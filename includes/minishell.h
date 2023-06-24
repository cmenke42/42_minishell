/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 00:10:38 by cmenke            #+#    #+#             */
/*   Updated: 2023/06/24 19:55:12 by user             ###   ########.fr       */
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


/// @brief The main data structure for a command.
/// @details This strucutre stores the information for one command.
/// @param envp_paths The paths to the commands. PATH= from envp.
/// @param cmd_path The path to the command.
/// @param cmd_args The arguments for the command.
/// @param input_fd The file descriptor for the input.
/// @param output_fd The file descriptor for the output.
/// @param next The next command in the command sequence.
typedef struct s_cmd_in_child
{
	//start at 0
	int						cmd_index;
	char					**envp_paths;
	char					*cmd_path;
	char					**cmd_args;
	//initially set to -1
	int						input_fd;
	//initially set to -1
	int						output_fd;
	struct s_cmd_in_child	*next;
}							t_child_cmd;

/// @brief The data structure for the tokens of a command line.
/// @details The node stores the information for one token.
/// @param token_index The index of the token in the command line.
/// @param token_type The type of the token.
/// @param token The token itself.
/// @param next The next token in the command line.
typedef struct s_tokens
{
	int					token_index;
	int					token_type;
	char				*token;
	struct s_tokens		*next;
}						t_tokens;


/// @brief The main data structure for minishell.
/// @param command The struct for one command of the command sequence.
/// @param envp The environment variables.
/// @param pipes All pipes that are used for the complete command sequence.
/// @param nbr_cmds The number of commands in the command sequence.
typedef struct s_data
{
	char			*line_read;
	bool			finished_input;
	t_child_cmd		*command;
	t_tokens		*tokens;
	int				token_index;
	char			**envp;
	int				**pipes;
	int				*pids;
	int				nbr_cmds;
}					t_data;


enum	e_token_id
{
	enum_word,
	command,
	single_quote,
	double_quote,
	op_input_redirection,
	op_here_doc,
	op_output_redirection_trunc,
	op_output_redirection_append,
	op_pipe,
	token_error
};

//sources
//fork_childs.c
void	ft_child_process_executor(t_data *data, t_child_cmd *command ,int i);
int		ft_fork_childs(t_data *data, int nbr_cmds);
//builtins
// echo.c
void	ft_echo(char **command);
// clearing
// ft_free_double_pointer.c
void	ft_free_double_pointer_char(char ***ptr);
void	ft_free_double_pointer_int(int ***ptr);
//clear_all.c
void	ft_clear_all_data(t_data *data);
//execution
// get_envp_cmd_paths.c
char	**ft_get_envp_paths(char **envp);
char	*ft_get_cmd_path(char **envp_paths, char *cmd);
// lexer_tokens
// lexer.c
bool	ft_create_tokens(t_data *data, char *line_read);
void	ft_skip_to_next_non_delim(char *line_read, int *i, int *start);
void	ft_skip_quote_block(char *cmd_line, int *i);

// token_analysis.c
bool	ft_put_id_to_token(t_data *data);
bool	ft_syntax_in_tokens(t_data *data);
// handle_operators.c
bool	ft_handle_operators(t_data *data);
// remove_quotes.c
bool	ft_remove_quotes_from_elements(t_tokens *token);

#endif