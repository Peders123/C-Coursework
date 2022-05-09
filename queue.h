#ifndef __QUEUE__
#define __QUEUE__ 1

#include <stdio.h>
#include <stdlib.h>

/*----- structure definition -------------------------------------------------*/

typedef struct Car {
    short time;
    struct Car *next;
} CAR;

typedef struct {
    CAR *front;
    CAR *rear;
    short length;
    int maxTime;
    int totalTime;
    int total;
    int timeToClear;
} QUEUE;

/*----- function prototypes --------------------------------------------------*/

extern void initQueue(QUEUE *);
extern void enqueue(QUEUE *);
extern void dequeue(QUEUE *);

#endif