/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 23:28:35 by cmenke            #+#    #+#             */
/*   Updated: 2023/06/15 16:31:48 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_clear_all_data(t_data *data)
{
	t_child_cmd	*temp;
	t_child_cmd	*temp2;

	temp = data->command;
	ft_free_double_pointer_char(&data->envp);
	ft_free_double_pointer_int(&data->pipes);
	if (data->pids)
	{
		free(data->pids);
		data->pids = NULL;
	}
	while (temp)
	{
		ft_free_double_pointer_char(&temp->envp_paths);
		if (temp->cmd_path)
		{
			free(temp->cmd_path);
			temp->cmd_path = NULL;
		}
		ft_free_double_pointer_char(&temp->cmd_args);
		temp2 = temp;
		temp = temp->next;
		free(temp2);
	}
}