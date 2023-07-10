/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 00:30:06 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/10 17:36:37 by cmenke           ###   ########.fr       */
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
	//rl_clear_history();
	exit(0);
}

//handles the ctrl-C key.
// rl_replace_line(PROMPT, 1); -> 1 clears the undo list
// of the current line (cmd z)
void ft_sig_sigint_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		//rl_replace_line("", 1);
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
	
	t_env *env = store_env(envp);
	while (1)
	{
		line_read = readline(PROMPT);
		if (line_read && *line_read)
		{
			add_history(line_read);
			// data->finished_input = false;
			if (!ft_strncmp(line_read, "env", ft_strlen("env")))
				print_env(env);
			if ((!ft_strncmp(line_read, "export", ft_strlen("export"))))
				export(env);
			if ((!ft_strncmp(line_read, "pwd", ft_strlen("pwd"))))
				ft_pwd();
			if ((!ft_strncmp(line_read, "exit", ft_strlen("exit"))))
				ft_exit();	
			// else
			// 	add_to_list(env, line_read);
			// else
			// 	remove_from_list(env, line_read);
			free(line_read);
		}
		else if (!line_read)
			ft_exit_ctrl_d();
	}
}
