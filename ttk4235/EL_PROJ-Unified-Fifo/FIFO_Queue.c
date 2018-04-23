#include "FIFO_Queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void FIFO_addFloor(Node** head, int floor) {
    
    // check if already added
    if (FIFO_floorInQueue(head, floor)){
        return;
    }

    Node* newNode = malloc(sizeof(Node));
    newNode->floor = floor;

    if (!(*head)){
        newNode->next = NULL;
    }
    else{
        newNode->next = *head;
    }

	*head = newNode; 
}

int FIFO_popTopPriority(Node** head) {
	int returnValue = -1;
    /* if queue is empty*/
    if (!(*head)){
        return returnValue;
    }

	/* if there is only one item in the list, remove it */
	if ((*head)->next == NULL) {
        returnValue = (*head)->floor;
        free(*head);
        *head = NULL;
        return returnValue;
    }

    /* get to the last node in the list */
    Node* current = *head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    /* now current points to the last item of the list, so let's remove current->next */
    returnValue = current->next->floor;
    free(current->next);
    current->next = NULL;
    return returnValue;
}

int FIFO_getTopPriority(Node** head) {
    int returnValue = -1;
    /* if queue is empty*/
    if (!(*head)){
        return returnValue;
    }

    /* if there is only one item in the list, remove it */
    if ((*head)->next == NULL) {
        returnValue = (*head)->floor;
        return returnValue;
    }

    /* get to the second to last node in the list */
    Node* current = *head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    /* now current points to the last item of the list, so let's get current->next */
    returnValue = current->next->floor;
    return returnValue;
}

int FIFO_popFloor(Node** head, int floor) {
    Node* previous, * current;

    if (*head == NULL) {
        return -1;
    }

    if ((*head)->floor == floor) {
        Node* next = (*head)->next;
        free(*head);
        *head = next;
        return floor;
    }

    previous = *head;
    current = (*head)->next;
    while (current) {
        if (current->floor == floor) {
            previous->next = current->next;
            free(current);
            return floor;
        }

        previous = current;
        current  = current->next;
    }
    return -1;
}

bool FIFO_floorInQueue(Node** head, int floor){
    Node* current = *head;

    while (current){
        if (current->floor == floor){
            return true;
        }

        current = current->next;
    }

    return false;
}

bool FIFO_isEmpty(Node** head){
    return *head == NULL;
}



void FIFO_deleteAll(Node** head){
    if (!(*head)){
        return; // queue empty
    }

    Node* current = *head;
    Node* prev;
    while (current->next){
        prev = current;
        current = current->next;
        free(prev);
    }
    free(current);
    *head = NULL;
}

void FIFO_printQueue(Node** head){
    Node* current = *head;

    while (current){
        printf("head = %p and current = %d\n", *head, current->floor);

        current = current->next;
    }
}