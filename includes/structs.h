/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 16:50:05 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/04 20:04:53 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

typedef struct s_shell_data
{
	int		exit_code;
	int		default_stdin;
	int		default_stdout;
	bool	print_quotes_for_oldpwd;
	char	*cmd_line; //in main shell it gets free in the main function
	char	**envp_array;
	int		**pipe_fds;	//gets freed in execution
	pid_t	*process_ids;
	char	**heredocs;
	t_list	*cmd_sequences;
	t_list	*all_tokens;	//same as cmd_sequences->tokens
	t_list	*env_list;
}				t_shell_data;

typedef struct s_command_sequences
{
	t_list	*tokens;	//are the same as in args
	char	**envp_command_paths; //free directly after use in execution
	char	*command_path;			//free in case of error in execution
	char	**args;
	int		input_fd;
	int		output_fd;
}				t_cmd_sequences;

typedef struct s_tokens
{
	char	*token;
	char	type;
	int		heredoc_number;
}				t_tokens;

typedef struct s_env
{
	char			*name;
	char			*value;
	bool			print_empty_quotes;
	struct s_env	*next;
}	t_env;

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

enum	e_error_codes
{
	__success,
	__no_history,
	__syntax_error,
	__system_call_error,
	__stop_execution,
	__mini_error,
	__no_builtin_found
};

enum e_variable_expansion_cases
{
	v_keep_dollar,
	v_exit_code,
	v_untrimmed_value,
	v_trim_value
};
