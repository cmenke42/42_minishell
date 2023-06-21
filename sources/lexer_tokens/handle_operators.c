/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:50:59 by cmenke            #+#    #+#             */
/*   Updated: 2023/06/21 20:27:58 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	ft_open_file_fds(char **argv, int files_fd[2])
{
	mode_t	mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	files_fd[0] = open(argv[1], O_RDONLY);
	if (files_fd[0] == -1)
		perror("infile");
	files_fd[1] = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, mode);
	if (files_fd[1] == -1)
		perror("outfile");
}


bool	ft_open_file_append_trunc(char *file_name)
{
	int	fd;
	mode_t	mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, mode);
	if (fd == -1)
	{
		perror("outfile");
		return (false);
	}
	return (true);
}

bool	ft_handle_operators(t_data *data)
{
	//1. expand variables - assume like this -> variable in and value out
	//2. here_doc
	//3. redirection
}