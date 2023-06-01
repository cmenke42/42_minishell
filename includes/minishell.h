/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 00:10:38 by cmenke            #+#    #+#             */
/*   Updated: 2023/06/02 01:35:27 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//custom
# include "../libft/libft.h"
# include "colors.h"

# include <stdio.h>
//readline
# include <readline/readline.h>
# include <readline/history.h>

//tc functions
# include <termios.h>

//signals
# include <signal.h>

// //terminal
// # include <sys/ttydefaults.h>

# define PROMPT "Minishell:$ "

typedef struct s_cmd_in_child
{
	char			*cmd_path;
	char			**cmd_args;
	char			**envp;
	int				input_fd;
	int				output_fd;
	int				pipe[2];
	int				files[2];
	pid_t			process_id;
	struct s_data	*next;
}					t_child_cmd;

typedef struct s_data
{
	t_child_cmd		*command;
}					t_data;

#endif