#ifndef __RUNONESIMULATION__
#define __RUNONESIMULATION__ 1

#include <queue.h>
#include <stdlib.h>

/*----- structure definition -------------------------------------------------*/

typedef struct Settings {
    int leftRate;
    int rightRate;
    int leftTime;
    int rightTime;
} SETTINGS;

typedef struct Data {
    float total;
    float average;
    float max;
    float time;
} DATA;

/*----- function prototypes --------------------------------------------------*/

extern DATA * runOneSimulation(int, int, int, int);
static void addTime(QUEUE *);
static void arrive(QUEUE *, int);
static void runIteration(QUEUE *, QUEUE *, int *, int *, SETTINGS, short);

#endif