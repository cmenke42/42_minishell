/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 00:10:38 by cmenke            #+#    #+#             */
/*   Updated: 2023/06/07 16:49:24 by cmenke           ###   ########.fr       */
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

#include <stdbool.h>

# define PROMPT "Minishell:$ "

/// @brief The main data structure for a command.
/// @details This strucutre stores the information for one command.
/// @param cmd_path The path to the command.
/// @param cmd_args The arguments for the command.
/// @param input_fd The file descriptor for the input.
/// @param output_fd The file descriptor for the output.
/// @param pipes All pipes that are used for the complete command sequence.
/// @param next The next command in the command sequence.
typedef struct s_cmd_in_child
{
	char					*cmd_path;
	char					**cmd_args;
	int						input_fd;
	int						output_fd;
	int						**pipes;
	struct s_cmd_in_child	*next;
}					t_child_cmd;

/// @brief The main data structure for minishell.
/// @param command The struct for one command of the command sequence.
/// @param envp The environment variables.
/// @param cmd_paths The paths to the commands. PATH= from envp.
typedef struct s_data
{
	t_child_cmd		*command;
	char			**envp;
	char			**cmd_paths;
}					t_data;

//sources
//fork_childs.c
void	ft_child_process_executor(t_data *data, t_child_cmd *command ,int i);
int		ft_fork_childs(t_data *data, int nbr_cmds);
#endif