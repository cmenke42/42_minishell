/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:16:48 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/20 21:53:38 by cmenke           ###   ########.fr       */
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
