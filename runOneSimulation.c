#include <runOneSimulation.h>

/* runs a single simulation on the input parameters */
DATA * runOneSimulation(int leftRate, int rightRate, int leftTime, int rightTime) {

    /* settings struct makes it easier to pass data */
    SETTINGS settings;

    settings.leftRate = leftRate;
    settings.rightRate = rightRate;
    settings.leftTime = leftTime;
    settings.rightTime = rightTime;

    QUEUE leftQueue;
    QUEUE rightQueue;

    initQueue(&leftQueue);
    initQueue(&rightQueue);

    int leftLight = leftTime;
    int rightLight = 0;
    short state = 0;

    short i;

    for (i = 0; i < 500; i++) {

        runIteration(&leftQueue, &rightQueue, &leftLight, &rightLight, settings, 0);

    }

    short x = 0;

    /* runs until both queues are clear */
    while ((leftQueue.length != 0) || (rightQueue.length != 0)) {

        /* if the queue is empty, set the time to clear to the number of iterations */
        if (leftQueue.length == 0 && leftQueue.timeToClear == -1) {
            leftQueue.timeToClear = x;
        }

        if (rightQueue.length == 0 && rightQueue.timeToClear == -1) {
            rightQueue.timeToClear = x;
        }

        runIteration(&leftQueue, &rightQueue, &leftLight, &rightLight, settings, 1);

        x++;

    }

    /* set the remaning time to clear as it is check at the start of the while loop, so won't be set */
    if (leftQueue.timeToClear == -1) {
        leftQueue.timeToClear = x;
    }

    if (rightQueue.timeToClear == -1) {
        rightQueue.timeToClear = x;
    }

    /* group the data into an array so it can be returned */
    static DATA data[2];

    DATA leftData;
    leftData.total = (float)leftQueue.total;
    leftData.average = (float)leftQueue.totalTime / (float)leftQueue.total;
    leftData.max = (float)leftQueue.maxTime;
    leftData.time = (float)leftQueue.timeToClear;

    DATA rightData;
    rightData.total = (float)rightQueue.total;
    rightData.average = (float)rightQueue.totalTime / (float)rightQueue.total;
    rightData.max = (float)rightQueue.maxTime;
    rightData.time = (float)rightQueue.timeToClear;

    data[0] = leftData;
    data[1] = rightData;

    return data;

}

/* adds one time unit to every car in the queue */
void addTime(QUEUE *queue) {

    if (queue->front == NULL) {
        return;
    }

    CAR *car = queue->front;

    while (car != NULL) {
        car->time++;
        car = car->next;
    }

}

/* if the random number between 1 and 100 is less than the rate, then a car is added */
void arrive(QUEUE *queue, int rate) {

    int r = 1 + rand() % 100;

    if (r <= rate) {
        enqueue(queue);
    }

}

/* runs a single iteration of the system */
void runIteration(QUEUE *leftQueue, QUEUE *rightQueue, int *leftLight, int *rightLight, SETTINGS settings, short stage) {

    addTime(leftQueue);
    addTime(rightQueue);

    /* if neither traffic light counter is positive, set the lower counter to the time passed in */
    if (*leftLight <= 0 && *rightLight <= 0) {
        if (*leftLight > *rightLight) {
            *rightLight = settings.rightTime;
        } else {
            *leftLight = settings.leftTime;
        }
    }
    
    else {
        /* if it is still the first 500 iterations, cars are allowed to join the queue */
        if (stage == 0) {
            arrive(leftQueue, settings.leftRate);
            arrive(rightQueue, settings.rightRate);
        }

        /* cars in the corresponding queue go through when the light is green */
        if (*leftLight > 0) {
            dequeue(leftQueue);
        } else {
            dequeue(rightQueue);
        }

        (*leftLight)--;
        (*rightLight)--;
    }

}