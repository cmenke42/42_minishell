/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_childs copy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 01:30:32 by cmenke            #+#    #+#             */
/*   Updated: 2023/06/08 12:33:52 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	ft_child_process_executor(t_data *data)
{
	//restoring defoult handling of SIGQUIT and SIGINT
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	
	//check cmd_path

	//manage redirection
	//close pipes
	//close files
	
	//call exeve or builtin

	//exit (with appropriate error_code)
	//and free

}

int	ft_fork_childs(t_data *data)
{
	t_child_cmd	*cmd_and_args;

	cmd_and_args = data->command;

	while (cmd_and_args)
	{
		if (cmd_and_args->next)
		{
			if (pipe(cmd_and_args->pipe) == -1);
				exit(1);
			//call the exit functio to stop things and clear up.
		}
		cmd_and_args->process_id = fork();
		if (cmd_and_args->process_id == -1)
		{
			perror("fork error");
			exit(1);
			//call the exit functio to stop things and clear up.
		}
		else if (cmd_and_args->process_id == 0)
		{
			//child
			//-> call a funciton with exit at the end.
		}
		else if (cmd_and_args->process_id > 0)
		{
			// parent
			//another iteration
		}
		cmd_and_args = cmd_and_args->next;
	}
	//close pipes

	//wait for childs to finish

	//collect exit status
}