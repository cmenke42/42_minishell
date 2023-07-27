/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double_pointer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:25:39 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/27 14:32:37 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_double_pointer_char(char ***ptr)
{
	int	i;
	char	**temp;
	
	if (!ptr)
		return ;
	temp = *ptr;
	i = 0;
	if (temp)
	{
		while (temp[i])
			free(temp[i++]);
		free(temp);
		*ptr = NULL;
	}
}

void	ft_free_double_pointer_int(int ***ptr, int size)
{
	int	i;
	int	**temp;
	
	i = 0;
	if (!ptr)
		return ;
	temp = *ptr;
	if (temp)
	{
		while (i < size)
			free(temp[i++]);
		free(temp); //unnecessary free causing issues
		*ptr = NULL;
	}
}

void	ft_free_pointer_and_set_to_null(void **ptr)
{
	if (!ptr || !*ptr)
		return ;
	free(*ptr);
	*ptr = NULL;
}