/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:16:48 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/20 23:16:39 by cmenke           ###   ########.fr       */
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

void ft_print_pipe_fds(int **pipe_fds, int number_of_pipes)
{
	int	i;

	i = 0;
	while (i < number_of_pipes)
	{
		printf("pipe_fds[%d][0] = %d\n", i, pipe_fds[i][0]);
		printf("pipe_fds[%d][1] = %d\n", i, pipe_fds[i][1]);
		i++;
	}
}

bool	ft_execute_commands(t_shell_data *shell_data)
{
	int	number_of_commands;

	number_of_commands = ft_lstsize(shell_data->command_sequences);
	if (!ft_create_pipes(&shell_data->pipe_fds, number_of_commands - 1))
		return (false);
	// if (number_of_commands == 1 // && builtin)
	// else
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
		ft_putnbr_fd(shell_data->process_ids[i], 2);
		// ft_putstr_fd("\n", 2);
		i++;
		command_sequences = command_sequences->next;
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
	if(!ft_manage_redirection_in_child((t_command_sequences *)sequence_to_execute->content, command_index, shell_data->pipe_fds, number_of_commands))
		;
	//find the correct path
	else if (execve(((t_command_sequences *)sequence_to_execute->content)->args[0], ((t_command_sequences *)sequence_to_execute->content)->args, shell_data->envp_array) == -1)
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
	return (true);
}

bool	ft_mange_input_redirection_in_child(int input_fd, int command_index, int **pipe_fds)
{
	if (input_fd == 0 && command_index == 0)
		return (true);
	if (input_fd > 0)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
			return (perror("error dup2 input_fd"), false);
	}
	else if (command_index > 0)
	{
		if (dup2(pipe_fds[command_index -1][0], STDIN_FILENO) == -1)
			return (perror("error dup2 pipe_fd_[0]"), false);
	}
	return (true);
}

bool	ft_manage_output_redirecion_in_child(int output_fd, int command_index, int **pipe_fds, int number_of_commands)
{
	if (output_fd == 0 && command_index == number_of_commands - 1)
		return (true);
	if (output_fd > 0)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
			return (perror("error dup2 output_fd"), false);
	}
	else if (command_index < number_of_commands - 1)
	{
		if (dup2(pipe_fds[command_index + 1][1], STDOUT_FILENO) == -1)
			return (perror("error dup2 pipe_fd_[1]"), false);
	}
	return (true);
}