#include <queue.h>

/*----- queue functions ------------------------------------------------------*/

/* sets up initial queue values */
void initQueue(QUEUE *queue) {

    queue->front = NULL;
    queue->rear = NULL;
    queue->length = 0;
    queue->maxTime = 0;
    queue->totalTime = 0;
    queue->total = 0;
    queue->timeToClear = -1;

}

/* adds a car to the back of the queue queue */
void enqueue(QUEUE *queue) {

    /* creates the car struct */
    CAR *car;
    if ((car = (CAR *)malloc(sizeof(CAR))) == NULL) {
        printf("Out of memory\n");
        exit(1);
    }
    car->time = 0;
    car->next = NULL;

    /* sets the pointers */
    if (queue->rear != NULL) {
        queue->rear->next = car;
    }
    queue->rear = car;

    if (queue->front == NULL) {
        queue->front = car;
    }

    queue->length++;
    queue->total++;

}

/* removes a car from the front of the queue */
void dequeue(QUEUE *queue) {

    if (queue->front == NULL) {
        return;
    }

    /* temporary pointer to avoid memory leaks */
    CAR *temp = queue->front;

    /* removes the car from the list */
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    queue->length--;
    queue->totalTime += temp->time;

    /* if the car exceeds the current max wait time, set its time to the max wait time */
    if (temp->time > queue->maxTime) {
        queue->maxTime = temp->time;
    }

    free(temp);

}