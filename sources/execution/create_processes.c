/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:16:48 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/19 17:36:58 by cmenke           ###   ########.fr       */
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

// bool	ft_execute_commands(t_shell_data *shell_data)
// {
// 	int	number_of_commands;

// 	number_of_commands = ft_get_number_of_commands()
// }