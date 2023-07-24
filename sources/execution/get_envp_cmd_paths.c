/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp_cmd_paths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:24:19 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/24 13:22:37 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_close_fd(int *files_fd, int *pipe_fd)
{
	if (files_fd)
	{
		if (files_fd[0] != -1)
			close(files_fd[0]);
		if (files_fd[1] != -1)
			close(files_fd[1]);
	}
	if (pipe_fd)
	{
		if (pipe_fd[0] != -1)
			close(pipe_fd[0]);
		if (pipe_fd[1] != -1)
			close(pipe_fd[1]);
	}
}

void	ft_free_close_err_exit(int *files_fd, int *pipe_fd, char **envp_paths,
							char *error_text)
{
	ft_close_fd(files_fd, pipe_fd);
	ft_free_double_pointer_char(&envp_paths);
	if (error_text)
	{
		perror(error_text);
		exit(1);
	}
}

static char	**ft_add_slash_to_envp_paths(char **envp_paths)
{
	char	**result;
	int		i;

	i = 0;
	while (envp_paths && envp_paths[i])
		i++;
	result = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!result)
		perror("Malloc error add slash");
	i = 0;
	while (envp_paths && envp_paths[i])
	{
		result[i] = ft_strjoin(envp_paths[i], "/");
		if (!result[i])
		{
			perror("Malloc error join slash");
			ft_free_double_pointer_char(&result);
			break ;
		}
		i++;
	}
	ft_free_double_pointer_char(&envp_paths);
	return (result);
}

char	**ft_get_envp_paths(char **envp)
{
	int		i;
	char	*path_string;
	char	**envp_paths;

	i = 0;
	path_string = NULL;
	envp_paths = NULL;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path_string = envp[i] + 5;
		i++;
	}
	if (path_string)
	{
		envp_paths = ft_split(path_string, ':');
		if (!envp_paths)
		{
			//what should be freed and what should be closed?
			ft_free_close_err_exit(NULL, NULL, NULL, "Malloc error envp paths");
		}
	}
	envp_paths = ft_add_slash_to_envp_paths(envp_paths);
	if (!envp_paths)
		exit(1);
	return (envp_paths);
}

//checks if the cmd is to be found in one of the paths specified by envp
char	*ft_get_cmd_path(char **envp_paths, char *cmd)
{
	int		i;
	char	*cmd_path;

	cmd_path = NULL;
	i = 0;
	while (envp_paths && envp_paths[i] && cmd)
	{
		cmd_path = ft_strjoin(envp_paths[i], cmd);
		if (!cmd_path)
		{
			perror("Malloc error cmd path");
			return (NULL);
		}
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		else
			free(cmd_path);
		i++;
	}
	return (NULL);
}