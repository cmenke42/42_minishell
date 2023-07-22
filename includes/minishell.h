/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 00:10:38 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/22 20:11:38 by cmenke           ###   ########.fr       */
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

# define RW_R__R__ 0644
typedef struct s_shell_data
{
	char	*command_line_read;
	char	**envp_array;
	int		**pipe_fds;
	pid_t	*process_ids;
	t_list	*command_sequences;
	t_list	*all_tokens;
	t_env	*env_list;
}				t_shell_data;

typedef struct s_command_sequences
{
	t_list	*tokens;
	char	**envp_command_paths;
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

enum e_token_type
{
	text,
	syntax_error,
	pipe_operator,
	redirection_in,
	redirection_in_heredoc,
	redirection_out_trunc,
	redirection_out_append,
	redirection_filename
};

extern const char* token_enum_to_string[][2]; //remove this

//main
//lexer
	//create_tokens.c
bool	ft_process_command_line(t_shell_data *shell_data);
bool	ft_create_tokens_for_sequence(char *command_line_read, t_list **command_sequences);
void	ft_skip_to_next_non_delimiter(char **command_line);
bool	ft_is_whitespace(char c);
bool	ft_find_next_token(char **string, char **start, t_list **tokens);
void	ft_skip_quote_block(char **string, bool	only_single_quotes);
void	ft_move_while_same_char(char **command_line, char c);
bool	ft_create_one_token(char *start, char *end, t_list **token);
	//set_token_types.c
bool	ft_is_syntax_error(t_shell_data *shell_data);
void	ft_set_token_types(void *node);
char	ft_get_token_type(char *string);
	// syntax_error.c
bool	ft_check_equal_quote_amt(char *s);
bool	ft_search_and_print_syntax_error(t_shell_data *shell_data);
bool	ft_check_for_syntax_error(t_tokens *token, t_tokens *next_token);
bool	ft_is_operator(char token_type);
	//split_in_sequences.c
bool	ft_split_tokens_in_sequences(t_shell_data *shell_data);
bool	ft_find_pipe_operator(t_list **tokens);
void	ft_cut_out_pipe_node(t_list **tokens, t_list *next_token_node);
bool	ft_assing_tokens_to_sequence(t_list *start_of_sequence, t_list **command_sequences);
	// expand_variables.c
bool	ft_search_for_variable_expansion(t_shell_data *shell_data);
bool	ft_expand_variable(t_list *tokens, t_env *env_list);
bool	ft_do_variable_expansion(t_tokens *token, t_env *env_list);
bool	ft_execute_specific_case_of_variable_expansion(char	**string, char **token, bool in_double_quotes, t_env *env_list);
bool	ft_is_char_quote(char c);
bool	ft_get_variable_name(char *string, char **variable_name);
char	*ft_get_variable_value(t_env *env, char	*variable_name);
bool	ft_replace_variable_name_with_value(char **string, char **token, char *name, char *value);
char	*ft_trim_variable_value(char *string);
	//redirections
void	loop_in_command_seq(t_shell_data *shell_data);

// ---
bool	ft_handle_redirection_operators(t_command_sequences *one_sequence, t_list *tokens);
bool	ft_do_redirection(int *input_fd, int *output_fd, char operator, t_tokens *file_token);
bool	ft_output_redirection(int *output_fd, char operator, t_tokens *file_token);
bool	ft_input_redirection(int *input_fd, char operator, t_tokens *file_token);
	//token_list_to_char_array
bool	ft_token_list_to_char_array(t_command_sequences *one_sequence);
int		ft_count_arguments(t_list *tokens);
void	ft_copy_token_from_list_to_array(char **arguments, int *i, char *token);
	//remove_quotes
char	*ft_remove_quotes_from_token(char **token);
int		ft_strlen_without_quotes(char *cmd_line);
void	ft_copy_element_without_quotes(char *cmd_line, char *new_line);
// clearing
	//ft_free_double_pointer.c
void	ft_free_double_pointer_char(char ***ptr);
void	ft_free_double_pointer_int(int ***ptr);
	// clear_all.c
void	ft_clear_token(void *token);
void	ft_clear_command_sequence(void *sequence);
// void	ft_free_command_sequences(void *command_sequences);

//execution
	//create_processes
bool	ft_execute_commands(t_shell_data *shell_data);
bool	ft_create_pipes(t_shell_data *shell_data, int number_of_pipes);
bool	ft_fork_child_processes(t_shell_data *shell_data, int number_of_commands);
int		ft_wait_for_child_processes_and_get_exit_code(t_shell_data *shell_data, int number_of_commands);
void	ft_get_exit_code(int *exit_code, int exit_status, int i, int number_of_commands);
	//execute_coammand_in_child
void	ft_execute_command_in_child(t_shell_data *shell_data, int number_of_commands, t_command_sequences *sequence_to_execute, int command_index);
bool	ft_execution_of_command(t_shell_data *shell_data, t_command_sequences *sequence_to_execute);
bool	ft_execute_builtin_if_builtin(t_shell_data *shell_data, t_command_sequences *sequence_to_execute);
bool	ft_check_if_cmd_path_is_valid(t_shell_data *shell_data, t_command_sequences *one_sequence);
	//duplication_of_fds_in_child
bool	ft_duplication_of_fds(int **pipe_fds, t_command_sequences *sequence_to_execute, int number_of_commands, int command_index);
bool	ft_input_redirection_in_child(int **pipe_fds, int input_fd, int command_index);
bool	ft_output_redirection_in_child(int **pipe_fds, int output_fd, int number_of_commands, int command_index);
void	ft_close_all_pipes(int **pipe_fds, int number_of_pipes);
	//get_envp_cmd_paths
char	*ft_get_cmd_path(char **envp_paths, char *cmd);
char	**ft_get_envp_paths(char **envp);
	//env_list_to_char_array
bool	ft_env_list_to_char_array(t_shell_data *shell_data);
int		ft_get_number_of_env_variables(t_env *env_list);
bool	ft_copy_env_from_list_to_array(t_shell_data *shell_data);
char	*ft_create_one_variable(t_env *one_variable);


// bool	ft_create_pipes(int ***pipe_fds, int number_of_pipes);
// bool	ft_execute_command_in_child(t_shell_data *shell_data, int number_of_commands);
// void	ft_command_execution_in_child_process(t_shell_data *shell_data, t_list *sequence_to_execute, int command_index, int number_of_commands);
// bool	ft_manage_redirection_in_child(t_command_sequences *sequence_to_execute, int command_index, int **pipe_fds, int number_of_commands);
// bool	ft_mange_input_redirection_in_child(int input_fd, int command_index, int **pipe_fds);
// bool	ft_manage_output_redirecion_in_child(int output_fd, int command_index, int **pipe_fds, int number_of_commands);
// bool	ft_check_if_cmd_path_is_valid(t_shell_data *shell_data, t_command_sequences *one_sequence);
// bool	ft_check_if_builtin(t_command_sequences *one_sequence);

// bool	ft_env_list_to_char_array(t_shell_data *shell_data);
// int		ft_get_number_of_env_variables(t_env *env_list);
// bool	ft_copy_env_from_list_to_array(t_shell_data *shell_data);
// char	*ft_create_one_variable(t_env *one_variable);
// void	ft_close_all_pipe_fds(int **pipe_fds, int number_of_pipes, int command_index);
// void	ft_close_one_pipe(int *one_pipe, int command_index, int i);


//heredoc
void	create_heredoc(t_tokens *command);


//helpers.c
	// void ft_print_list(t_list *list);
void	ft_print_token_list(t_list *tokens);
void	ft_print_command_sequences(t_list *command_sequences);
void	ft_print_tokens_and_type(t_list *tokens);//
void	ft_print_command_sequences_args(t_list *command_sequences);
void	ft_print_double_array(char **array);
void	ft_print_envp_array(char **envp_array);
void	ft_print_pipe_fds(int **pipe_fds, int number_of_pipes);

#endif