#include "../../includes/env.h"

t_env *remove_from_list(t_env* head, char* name) {
    // Check if the list is empty
    if (head == NULL) {
        printf("List is empty.\n");
        return NULL;
    }

    // Store the head node and a reference to the previous node
    t_env* current = head;
    t_env* previous = NULL;

    // Check if the head node contains the name to be deleted
    if (current != NULL && ft_strncmp(current->name, name, ft_strlen(current->name)) == 0) {
        head = current->next; // Update the head to the next node
        free(current->name); // Free the memory of the deleted name
        free(current->value); // Free the memory of the deleted value
		current->value = 0;
        free(current); // Free the memory of the deleted node
        printf("Node with name %s deleted.\n", name);
        return head;
    }

    // Search for the node with the given name
    while (current != NULL && ft_strncmp(current->name, name, ft_strlen(current->name)) != 0) {
        previous = current;
        current = current->next;
    }

    // If the name was not found in the list
    if (current == NULL) {
        printf("Node with name %s not found.\n", name);
        return head;
    }

    // Adjust the pointers to remove the node
    previous->next = current->next;

    // Free the memory of the deleted node

    free(current->name);
    free(current->value);
    free(current);
    printf("Node with name %s deleted.\n", name);
    return head;
}
