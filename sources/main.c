/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 00:30:06 by cmenke            #+#    #+#             */
/*   Updated: 2023/06/02 01:30:18 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_double_pointer(char **string)
{
	int i;
	
	i = 0;
	while (string && string[i])
		printf("%s\n", string[i++]);
}


//take care that it frees all neccessary things
void	ft_exit_ctrl_d()
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	rl_clear_history();
	exit(0);
}

//handles the ctrl-C key.
// rl_replace_line(PROMPT, 1); -> 1 clears the undo list
// of the current line (cmd z)
void ft_sig_sigint_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		rl_replace_line("", 1);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	//add functionality to send signal to child process
}

int	main(int argc, char **argv, char **envp)
{
	char	*line_read;
	t_data	*data;

	// ft_print_double_pointer(envp);

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		perror("struct allocation error");

	//to ignore the SIG_QUIT signal from ctrl- Backslash
	signal(SIGQUIT, SIG_IGN);
	// handles the ctrl-C key.
	signal(SIGINT, ft_sig_sigint_handler);
	while (1)
	{
		line_read = readline(PROMPT);
		if (line_read && *line_read && *line_read != ' ')
		{
			add_history(line_read);
			free(line_read);
		}
		else if (!line_read)
			ft_exit_ctrl_d();
	}
}
