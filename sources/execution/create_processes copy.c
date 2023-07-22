/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:16:48 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/22 16:47:01 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//go through the tokens and then put the token contents as arguments for the execution part.
	//delete the token list after finishing this process.
	//if something goes wrong in that process stop the execution of that process??
//after that go on with finding the command path
	//check the 4 different options
		//builtin
		//path
		//comannd
		//executabel
//then exccute the command
	//if execution fails free all the content that was brought into the child process which is allocated
	//save the exit status of that command


// -----

//start with how many pipes are neeeded -> number of command_sequences - 1
	//store the pipes in an 2 d array

//then fork processes for each command_sequences existing
	//When to fork:
		// more than one process
		//no builtin

//start to call the functions in the child process to prepare the command
	//handle redirections,...

//close unneeded file descriptors

bool	ft_execute_commands(t_shell_data *shell_data)
{
	int	number_of_commands;

	number_of_commands = ft_lstsize(shell_data->command_sequences);
	if (!ft_create_pipes(&shell_data->pipe_fds, number_of_commands - 1))
		return (false);
	// if (number_of_commands == 1 // && builtin)
	// else
	ft_print_pipe_fds(shell_data->pipe_fds, number_of_commands - 1);
	if (!ft_execute_command_in_child(shell_data, number_of_commands))
		return (false);
	return (true);
}

bool	ft_create_pipes(int ***pipe_fds, int number_of_pipes)
{
	int	i;

	if (number_of_pipes == 0)
		return (true);
	*pipe_fds = (int **)ft_calloc(number_of_pipes, sizeof(int *));
	if (!*pipe_fds)
		return (perror("error creating pipe_fds array"), false);
	i = 0;
	while (i < number_of_pipes)
	{
		(*pipe_fds)[i] = (int *)ft_calloc(2, sizeof(int));
		if (!(*pipe_fds)[i])
			return (perror("error creating pipe_fds array"), false); //free and close later in clear function
		if (pipe((*pipe_fds)[i]) == -1)
			return(perror("error creating pipe"), false);
		i++;
	}
	return (true);
}

bool	ft_execute_command_in_child(t_shell_data *shell_data, int number_of_commands)
{
	int	i;
	t_list *command_sequences;

	command_sequences = shell_data->command_sequences;
	shell_data->process_ids = ft_calloc(number_of_commands, sizeof(pid_t));
	if (!shell_data->process_ids)
		return (perror("error creating process ids array"), false);
	i = 0;
	//counter to make sure you execute the right command in each child
	while (i < number_of_commands)
	{
		shell_data->process_ids[i] = fork();
		if (shell_data->process_ids[i] == -1)
			return (perror("error creating new process with fork"), false);
		if (shell_data->process_ids[i] == 0)
		{
			ft_command_execution_in_child_process(shell_data, command_sequences, i, number_of_commands);
			exit(22);
		}
		// ft_putnbr_fd(shell_data->process_ids[i], 2);
		// ft_putstr_fd("\n", 2);
		i++;
		command_sequences = command_sequences->next;
	}
	// ft_close_all_pipe_fds(shell_data->pipe_fds, number_of_commands - 1, -1);
	close(3);
	close(4);
	while (i >= 0)
	{
		i--;
		waitpid(shell_data->process_ids[i], NULL, 0);
	}
	return (true);
}

void	ft_command_execution_in_child_process(t_shell_data *shell_data, t_list *sequence_to_execute, int command_index, int number_of_commands)
{
	//check if the command is valid and find out which type it is
		//builtin
		//path, file
		//part of the envp PATH
	
	// manage redirection
	if (!ft_handle_redirection_in_sequences(sequence_to_execute))
	{
		;
	}
	if (!ft_tokens_lists_to_char_array(sequence_to_execute))
	{
		;
	}
	if(!ft_manage_redirection_in_child((t_command_sequences *)sequence_to_execute->content, command_index, shell_data->pipe_fds, number_of_commands))
		// ft_close_all_pipe_fds(shell_data->pipe_fds, number_of_commands - 1);
		;
	else if (!ft_env_list_to_char_array(shell_data))
		; //add the right exit code
	else if (!ft_check_if_cmd_path_is_valid(shell_data, (t_command_sequences *)sequence_to_execute->content))
	{
		perror("command not found"); //start with clearing procedure
		exit(127); //add the right exit code
	}
	//find the correct path

	else if (execve(((t_command_sequences *)sequence_to_execute->content)->command_path, ((t_command_sequences *)sequence_to_execute->content)->args, shell_data->envp_array) == -1)
		perror("execve error"); //start with clearing procedure
	//if execve failed
		//cleanup
	exit(1); //add the right exit code
}

		//if there is a file for redirection present -> 1.
		// if not use the pipe
			//exists?
			//i = 0
				//read from file or stdin
				//write to pipe [0][1]
			// i = 1, ...
				//read from pipe [i - 1][0]
				//write to pipe [i][1]
			// i - 1 = max
				//read from pipe [max][0]
				//write to file or stdout
bool	ft_manage_redirection_in_child(t_command_sequences *sequence_to_execute, int command_index, int **pipe_fds, int number_of_commands)
{
	if (!ft_mange_input_redirection_in_child(sequence_to_execute->input_fd, command_index, pipe_fds))
		return (false);
	if (!ft_manage_output_redirecion_in_child(sequence_to_execute->output_fd, command_index, pipe_fds, number_of_commands))
		return (false);
	// ft_close_all_pipe_fds(pipe_fds, number_of_commands - 1, command_index);
	return (true);
}

bool	ft_mange_input_redirection_in_child(int input_fd, int command_index, int **pipe_fds)
{
	// if (input_fd == 0 && command_index == 0)
	// 	return (true);
	if (input_fd > 0)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			close(input_fd);
			return (perror("error dup2 input_fd"), false);
		}
	}
	else if (command_index > 0)
	{
		// if (dup2(pipe_fds[command_index -1][0], STDIN_FILENO) == -1)
		// 	return (perror("error dup2 pipe_fd_[0]"), false);
		dup2(3, STDIN_FILENO);
	}
	return (true);
}

bool	ft_manage_output_redirecion_in_child(int output_fd, int command_index, int **pipe_fds, int number_of_commands)
{
	// if (output_fd == 0 && command_index == number_of_commands - 1)
	// 	return (true);
	if (output_fd > 0)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
		{
			close(output_fd);
			return (perror("error dup2 output_fd"), false);
		}
		
	}
	else if (command_index < number_of_commands - 1)
	{
		// if (dup2(pipe_fds[command_index][1], STDOUT_FILENO) == -1)
		// 	return (perror("error dup2 pipe_fd_[1]"), false);
		dup2(4, STDOUT_FILENO);
	}
	if (command_index == number_of_commands - 1)
		close(4);
	if (command_index == 0)
		close(3);
	return (true);
}

bool	ft_check_if_cmd_path_is_valid(t_shell_data *shell_data, t_command_sequences *one_sequence)
{
	//do we need to chek if cmd_args is NULL?
	//check if the command is a builtin
	if (ft_check_if_builtin(one_sequence) == true)
	{
		return (true);
	}
	//check if the command is a relative path or an absolute path
	if (access(one_sequence->args[0], X_OK) == 0)
	{
		ft_putstr_fd("relative path or absolute path found\n", 2);
		ft_putstr_fd(one_sequence->args[0], 2);
		return (true);
	}
	//check if the command is in the PATH from envp
	if (!ft_env_list_to_char_array(shell_data))
		return (false);
	one_sequence->envp_command_paths = ft_get_envp_paths(shell_data->envp_array);
	one_sequence->command_path = ft_get_cmd_path(one_sequence->envp_command_paths, one_sequence->args[0]);
	if (one_sequence->command_path)
	{
		// ft_putstr_fd("command found in PATH: ", 2);
		// ft_putstr_fd(one_sequence->command_path, 2);
		return (true);
	}
	//check if the command path is valid
	//if not, print error message and return false
	//if valid, return true
	return (false);
}

bool	ft_check_if_builtin(t_command_sequences *one_sequence)
{
	int		cmd_length;
	char	*command;

	command = one_sequence->args[0];
	cmd_length = 0;
	cmd_length = ft_strlen(command);
	//how to manage the calling of the builtin and the correct closing of the pipes, redirection and freeing?
	if (cmd_length < 2 || cmd_length > 6)
		return (false);
	if (ft_strncmp("echo", command, cmd_length) == 0)
		ft_putstr_fd("builtin echo\n", 2);
	else if (ft_strncmp("cd", command, cmd_length) == 0)
		ft_putstr_fd("builtin cd\n", 2);
	else if (ft_strncmp("pwd", command, cmd_length) == 0)
		ft_putstr_fd("builtin pwd\n", 2);
	else if (ft_strncmp("export", command, cmd_length) == 0)
		ft_putstr_fd("builtin export\n", 2);
	else if (ft_strncmp("unset", command, cmd_length) == 0)
		ft_putstr_fd("builtin unset\n", 2);
	else if (ft_strncmp("env", command, cmd_length) == 0)
		ft_putstr_fd("builtin env\n", 2);
	else if (ft_strncmp("exit", command, cmd_length) == 0)
		ft_putstr_fd("builtin exit\n", 2);
	else
		return (false);
	exit(42); //remove later
}

bool	ft_env_list_to_char_array(t_shell_data *shell_data)
{
	t_env	*env_list;
	int		number_of_env_variables;

	env_list = shell_data->env_list;
	number_of_env_variables = ft_get_number_of_env_variables(env_list);
	shell_data->envp_array = ft_calloc(number_of_env_variables + 1, sizeof(char *));
	if (!shell_data->envp_array)
		return (perror("error allocating envp array"), false);
	if (!ft_copy_env_from_list_to_array(shell_data))
		return (false);
	return (true);
}

int	ft_get_number_of_env_variables(t_env *env_list)
{
	int	number_of_env_variables;

	number_of_env_variables = 0;
	while (env_list)
	{
		number_of_env_variables++;
		env_list = env_list->next;
	}
	return (number_of_env_variables);
}

bool	ft_copy_env_from_list_to_array(t_shell_data *shell_data)
{
	t_env	*env_list;
	int		i;

	env_list = shell_data->env_list;
	i = 0;
	while (env_list)
	{
		shell_data->envp_array[i] = ft_create_one_variable(env_list);
		if (!shell_data->envp_array[i])
			return (false);
		i++;
		env_list = env_list->next;
	}
	return (true);
}

char	*ft_create_one_variable(t_env *one_variable)
{
	char	*env_variable;
	char	*name_and_equal_sign;

	name_and_equal_sign = NULL;
	env_variable = NULL;
	name_and_equal_sign = ft_strjoin(one_variable->name, "=");
	if (!name_and_equal_sign)
		return (perror("error creating env name_and_equal_sign"), NULL);
	if (one_variable->value)
	{
		env_variable = ft_strjoin(name_and_equal_sign, one_variable->value);
		free(name_and_equal_sign);
		if (!env_variable)
			return (perror("error creating env_variable"), NULL);
		return (env_variable);
	}
	return (name_and_equal_sign);
}

void	ft_close_all_pipe_fds(int **pipe_fds, int number_of_pipes, int command_index)
{
	int	i;

	i = 0;
	while (i < number_of_pipes)
	{
		ft_close_one_pipe(pipe_fds[i], command_index, i);
		i++;
	}
}

void	ft_close_one_pipe(int *one_pipe, int command_index, int i)
{
	if (command_index == -1 || command_index - 1 != i)
	{
		close(one_pipe[0]);
	}
	if (command_index == -1 || command_index != i)
	{
		close(one_pipe[1]);
	}
}