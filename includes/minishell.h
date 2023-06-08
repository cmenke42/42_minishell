/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 00:10:38 by cmenke            #+#    #+#             */
/*   Updated: 2023/06/08 15:44:56 by cmenke           ###   ########.fr       */
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
/// @param envp_paths The paths to the commands. PATH= from envp.
/// @param cmd_path The path to the command.
/// @param cmd_args The arguments for the command.
/// @param input_fd The file descriptor for the input.
/// @param output_fd The file descriptor for the output.
/// @param pipes All pipes that are used for the complete command sequence.
/// @param next The next command in the command sequence.
typedef struct s_cmd_in_child
{
	//start at 0
	int						cmd_nbr;
	char					**envp_paths;
	char					*cmd_path;
	char					**cmd_args;
	//initially set to -1
	int						input_fd;
	//initially set to -1
	int						output_fd;
	int						**pipes;
	struct s_cmd_in_child	*next;
}					t_child_cmd;

/// @brief The main data structure for minishell.
/// @param command The struct for one command of the command sequence.
/// @param envp The environment variables.
typedef struct s_data
{
	t_child_cmd		*command;
	char			**envp;
}					t_data;

//sources
//fork_childs.c
void	ft_child_process_executor(t_data *data, t_child_cmd *command ,int i);
int		ft_fork_childs(t_data *data, int nbr_cmds);
//builtins
// echo.c
void	ft_echo(char **command);
// clearing
// ft_free_double_pointer.c
char	**ft_free_double_pointer(char **ptr);
//execution
// get_envp_cmd_paths.c
char	**ft_get_envp_paths(char **envp);
char	*ft_get_cmd_path(char **envp_paths, char *cmd);

#endif