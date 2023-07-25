/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:30:47 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/25 14:39:00 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

t_env *remove_from_list(t_env* head, char* name) {
    // Check if the list is empty
    if (head == NULL) {
        return NULL;
    }

    // Store the head node and a reference to the previous node
    t_env* current = head;
    t_env* previous = NULL;

    // Check if the head node contains the name to be deleted
    if (current != NULL && ft_strcmp(current->name, name) == 0) {
        head = current->next; // Update the head to the next node
        free(current->name); // Free the memory of the deleted name
        free(current->value); // Free the memory of the deleted value
		current->value = 0;
        free(current); // Free the memory of the deleted node
        return head;
    }

    // Search for the node with the given name
    while (current != NULL && ft_strcmp(current->name, name) != 0) {
        previous = current;
        current = current->next;
    }

    // If the name was not found in the list
    if (current == NULL) {
        return head;
    }

    // Adjust the pointers to remove the node
    previous->next = current->next;

    // Free the memory of the deleted node

    free(current->name);
    free(current->value);
    free(current);
    return head;
}

void    ft_unset(char **command, t_env *env)
{
    int i;

    i = 1;
    if (command[1])
    {
        while (command[i])
            remove_from_list(env, command[i++]);
    }
    else
        return ;
}