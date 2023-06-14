/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double_pointer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:25:39 by cmenke            #+#    #+#             */
/*   Updated: 2023/06/14 23:13:21 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_double_pointer_char(char ***ptr)
{
	int	i;
	char	**temp;
	
	i = 0;
	if (!ptr)
		return ;
	temp = *ptr;
	if (temp)
	{
		while (temp[i])
			free(temp[i++]);
		free(temp);
		temp = NULL;
	}
	return ;
}

void	ft_free_double_pointer_int(int ***ptr)
{
	int	i;
	int	**temp;
	
	i = 0;
	if (!ptr)
		return ;
	temp = *ptr;
	if (temp)
	{
		while (temp[i])
			free(temp[i++]);
		free(temp);
		temp = NULL;
	}
	return ;
}
