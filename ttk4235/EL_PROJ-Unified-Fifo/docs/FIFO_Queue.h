#pragma once
#include <stdbool.h>

typedef struct Node_t {
        int floor;
        int waitCount;
        struct Node_t* next;
} Node;


/* 	Adds floor to queue with lowest priority. 
	Doesn't do anything if already in queue
*/
void FIFO_addFloor(Node** head, int floor);

/* 	Get and remove highest priority item from queue.
	Return -1 if queue is empty.
	Return floor number on success. 	*/
int FIFO_popTopPriority(Node** head);

/*	Get and remove lowest priority item from queue.
	Return -1 if queue is empty.
	Return floor number on success. */ 
int FIFO_popLowestPriority(Node** head);

/*	Get top priority floor from queue.
	Return floor on success. 
	Return -1 on empty queue.
*/
int FIFO_getTopPriority(Node** head);

/*	Find and remove specified floor from queue. 
	Return -1 if queue is empty or floor not in queue.
	Return floor number on success. 
*/
int FIFO_popFloor(Node** head, int floor);

/*	Return true (1) if floor is in queue
	Return false (0) otherwise.
*/
bool FIFO_floorInQueue(Node** head, int floor);


/*	Return true if queue is empty
*/ 
bool FIFO_isEmpty(Node** head);

/*	Delete all orders from queue. 	*/
void FIFO_deleteAll(Node** head);

/* 	Print all nodes in prioritized order */
void FIFO_printQueue(Node** head);