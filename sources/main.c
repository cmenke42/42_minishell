/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 00:30:06 by cmenke            #+#    #+#             */
/*   Updated: 2023/06/07 14:49:34 by cmenke           ###   ########.fr       */
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



// bool	ft_initialize_command_struct(t_data *data, char **envp)
// {
// 	t_child_cmd *commands;

// 	commands = ft_calloc(1, sizeof(t_child_cmd));
// 	if (!commands)
// 	{
// 		perror("command struct allocation error");
// 		return (false);
// 	}
// 	commands->cmd_path = "/bin/cat";
// 	commands->cmd_args = ft_calloc(3, sizeof(char *));
// 	commands->cmd_args[0] = "cat";
// 	commands->cmd_args[1] = "main.c";
// 	commands->cmd_args[2] = NULL;
// 	commands->envp = envp;
// 	commands->input_fd = STDIN_FILENO;
// 	commands->output_fd = STDOUT_FILENO;
// 	commands->next = NULL;
// 	data->command = commands;
// 	return (true);
// }

int	main(int argc, char **argv, char **envp)
{
	char	*line_read;
	t_data	*data;

	// ft_print_double_pointer(envp);

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		perror("struct allocation error");
	// ft_initialize_command_struct(data, envp);
	printf("welcome to minishell\n");
	printf("exit_code last schild:%d\n", ft_fork_childs(data, 8));
	exit(0);

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
