/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 00:10:38 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/31 19:41:57 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <sys/param.h>
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

//lstat
#include <sys/stat.h>

//custom
# include "../libft/libft.h"
# include "structs.h"
# include "env.h"
# include "colors.h"

# define PROMPT "Minishell:$ "
# define SQUOTE_ERROR "minishell: syntax error while looking for matching `''"
# define DQUOTE_ERROR "minishell: syntax error while looking for matching `\"'"

# define RW_R__R__ 0644

extern int g_signal_number;

extern const char* token_enum_to_string[][2]; //remove this

//main
int		ft_process_command_line(t_shell_data *shell_data);
void	ft_set_minisell_signals(void);
void	ft_restore_default_signals(void);
void	ft_sig_sigint_handler_parent_execution(int sig_num);
void	ft_set_singals_handler_while_parent_execution(void);
int		ft_prepare_env_variables(t_shell_data *shell_data);
void	ft_delete_heredoc_files(char **heredoc_files);
//shlvl
int	increase_shlvl(t_list **env_list);
//lexer
	//create_tokens.c
int		ft_create_tokens_for_sequence(char *command_line_read, t_list **command_sequences);
void	ft_skip_to_next_non_delimiter(char **command_line);
bool	ft_is_whitespace(char c);
int		ft_find_next_token(char **string, char **start, t_list **tokens);
void	ft_skip_quote_block(char **string, bool	only_single_quotes);
void	ft_move_while_same_char(char **command_line, char c);
bool	ft_create_one_token(char *start, char *end, t_list **token);
	//set_token_types.c
bool	ft_is_syntax_error(t_shell_data *shell_data);
void	ft_set_token_types(void *node);
char	ft_get_token_type(char *string);
	// syntax_error.c
int		ft_check_equal_quote_amt(char *s);
bool	ft_search_and_print_syntax_error(t_shell_data *shell_data);
bool	ft_check_for_syntax_error(t_tokens *token, t_tokens *next_token);
bool	ft_is_operator(char token_type);
void	ft_print_syntax_error(t_tokens *token);
	//split_in_sequences.c
int		ft_split_tokens_in_sequences(t_shell_data *shell_data);
bool	ft_find_pipe_operator(t_list **tokens);
void	ft_cut_out_pipe_node(t_list **tokens, t_list *next_token_node);
bool	ft_assing_tokens_to_sequence(t_list *start_of_sequence, t_list **command_sequences);
	// expand_variables.c
// bool	ft_search_for_variable_expansion(t_shell_data *shell_data);
bool	ft_expand_variables(t_list *tokens, t_shell_data *shell_data);
bool	ft_do_variable_expansion(t_tokens *token, t_shell_data *shell_data);
bool	ft_execute_specific_case_of_variable_expansion(char	**string, char **token, bool in_double_quotes, t_shell_data *shell_data);
bool	ft_is_char_quote(char c);
bool	ft_get_variable_name(char *string, char **variable_name);
char	*ft_get_variable_value(t_list *env_list, char *variable_name);
bool	ft_replace_variable_name_with_value(char **string, char **token, char *name, char *value);
char	*ft_trim_variable_value(char *string);
void	ft_cut_out_empty_node(t_list **tokens, t_list *previous_token_node);

// ---
int		ft_handle_redirection_operators(t_command_sequences *one_sequence, t_list *tokens_of_sequence, t_shell_data *shell_data);
int		ft_do_redirection(t_command_sequences *one_sequence, t_tokens *operator_token, t_tokens *file_token, t_shell_data *shell_data);
int		ft_output_redirection(int *output_fd, char operator, t_tokens *file_token);
int		ft_input_redirection(int *input_fd, t_tokens *operator_token, t_tokens *file_token, t_shell_data *shell_data);
void	ft_put_redirection_error(char *file);
	//token_list_to_char_array
bool	ft_token_list_to_args_array(t_command_sequences *one_sequence);
int		ft_count_arguments(t_list *tokens);
void	ft_copy_token_from_list_to_array(char **arguments, int *i, char **token);
	//remove_quotes
bool	ft_remove_quotes_from_token(char **token);
int		ft_strlen_without_quotes(char *cmd_line);
void	ft_copy_element_without_quotes(char *cmd_line, char *new_line);
	//heredoc
int		ft_handle_heredocs(t_shell_data *shell_data);
int		ft_read_heredocs_in_child_process(t_shell_data *shell_data);
bool	ft_open_reading_for_heredocs(t_list *tokens, char **heredocs, t_shell_data *shell_data);
bool	ft_create_heredoc_names(t_shell_data *shell_data);
int		ft_count_heredocs(t_list *tokens);
char	*ft_create_here_doc_name(int i);
bool	ft_fill_heredoc(char *heredoc_name, char *delimiter, t_shell_data *shell_data);
bool	ft_is_quotes_in_delimiter(char *string);
bool	ft_expand_variables_in_heredoc_line(char **line, t_shell_data *shell_data);
// bool	ft_create_heredoc_names(t_shell_data *shell_data);
// int		ft_count_heredocs(t_list *tokens);
// char	*ft_create_here_doc_name(int i);
// bool	ft_create_and_save_heredocs(t_list *tokens_of_sequence, int *i);
// char	*create_heredoc(t_tokens *command, int *i);
// int		ft_create_heredoc_file(char **heredoc_filename, int *i);
// clearing
	//ft_free_double_pointer.c
void	ft_free_double_pointer_char(char ***ptr);
void	ft_free_double_pointer_int(int ***ptr, int size);
void	ft_free_pointer_and_set_to_null(void **ptr);
	// clear_all.c
void	ft_clear_token(void *token);
void	ft_clear_command_sequence(void *sequence);
	//clear_structs
void	ft_free_shell_data(t_shell_data *shell_data, bool everything);
void	ft_clear_command_sequence(void *node);
void	ft_clear_token(void *node);
void	ft_clear_env_variable(void *node);
// void	ft_free_command_sequences(void *command_sequences);

//execution
	//create_processes
int		ft_execute_commands(t_shell_data *shell_data);
bool	ft_create_pipes(t_shell_data *shell_data, int number_of_pipes);
bool	ft_fork_child_processes(t_shell_data *shell_data, int number_of_commands);
void	ft_wait_for_child_processes_and_get_exit_code(t_shell_data *shell_data, int number_of_commands);
void	ft_get_exit_code(int *exit_code, int stat_loc, bool first_encounter, bool reset_signal_number);
	//execute_coammand_in_child
void	ft_execute_command_in_child(t_shell_data *shell_data, int number_of_commands, t_command_sequences *sequence_to_execute, int command_index);
int		ft_execution_of_command(t_shell_data *shell_data, t_command_sequences *sequence_to_execute, bool single_builtin);
int		ft_execute_builtin_if_builtin(t_shell_data *shell_data, t_command_sequences *sequence_to_execute);
bool	ft_check_if_cmd_path_is_valid(t_shell_data *shell_data, t_command_sequences *sequence_to_execute);
void	ft_print_error(char *command, char *error_message);
bool	ft_is_slash_in_command(char *command);
	//single_builtin_execution
int		ft_execute_single_builtin(t_shell_data *shell_data, int number_of_commands, t_command_sequences *sequence_to_execute, int command_index);
bool	ft_is_builtin(t_command_sequences *sequence_to_execute);
bool	ft_save_standard_fds(t_shell_data *shell_data);
bool	ft_restore_standard_fds(t_shell_data *shell_data);
	//duplication_of_fds_in_child
bool	ft_duplication_of_fds(int **pipe_fds, t_command_sequences *sequence_to_execute, int number_of_commands, int command_index);
bool	ft_input_redirection_in_child(int **pipe_fds, int input_fd, int command_index);
bool	ft_output_redirection_in_child(int **pipe_fds, int output_fd, int number_of_commands, int command_index);
void	ft_close_all_pipes(int **pipe_fds, int number_of_pipes);
	//get_envp_cmd_paths
char	*ft_get_cmd_path(char **envp_paths, char *cmd);
char	**ft_get_envp_paths(char **envp);
	//env_list_to_char_array
bool	ft_env_list_to_envp_array(t_shell_data *shell_data);
char	*ft_create_one_env_variable(t_env *one_variable);

//delete!!!!
//helpers.c
	// void ft_print_list(t_list *list);
void	ft_print_token_list(t_list *tokens);
void	ft_print_command_sequences(t_list *command_sequences);
void	ft_print_tokens_and_type(t_list *tokens);//
void	ft_print_command_sequences_args(t_list *command_sequences);/////////////
void	ft_print_double_array(char **array);
void	ft_print_envp_array(char **envp_array);
void	ft_print_pipe_fds(int **pipe_fds, int number_of_pipes);
void	ft_print_command_sequences(t_list *command_sequences);
void	ft_print_token_list(t_list *tokens);
void	ft_print_double_array(char **array);
void	ft_print_command_sequences_args(t_list *command_sequences);
void	ft_print_tokens_and_type(t_list *tokens);

#endif