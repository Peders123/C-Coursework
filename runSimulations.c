#include <runSimulations.h>


int main(int argc, char **argv) {

    /* checks if there are only 4 input parameters */
    if (argc != 5) {
        return 1;
    }

    /* checks if all the parameters are positive numbers */
    short i;
    for (i=1; i<argc; i++) {
        if (isNumber(argv[i]) == 1) {
            return 1;
        }
    }

    srand(time(0));

    /* holds all the data for the results */
    DATA leftResults;
    DATA rightResults;

    leftResults.total = 0;
    leftResults.average = 0;
    leftResults.max = 0;
    leftResults.time = 0;

    rightResults.total = 0;
    rightResults.average = 0;
    rightResults.max = 0;
    rightResults.time = 0;

    /* get the command line parameters */
    int leftRate = atoi(argv[1]);
    int rightRate = atoi(argv[2]);
    int leftTime = atoi(argv[3]);
    int rightTime = atoi(argv[4]);

    DATA * data;

    /* runs the 100 simulations and adds the results to the totals */
    for (i = 0; i < 100; i++) {
        data = runOneSimulation(leftRate, rightRate, leftTime, rightTime);

        leftResults.total += data->total;
        leftResults.average += data->average;
        leftResults.max += data->max;
        leftResults.time += data->time;

        rightResults.total += (data+1)->total;
        rightResults.average += (data+1)->average;
        rightResults.max += (data+1)->max;
        rightResults.time += (data+1)->time;

    }

    if (leftRate == 0) {
        leftResults.average = 0;
    }

    if (rightRate == 0) {
        rightResults.average = 0;
    }

    /* displays the data */
    printf("Parameter values:\n");
    printf("   from left:\n");
    printf("      traffic arrival rate: %6.2f\n", (float)leftRate/100);
    printf("      traffic light period: %6d\n", leftTime);
    printf("   from right:\n");
    printf("      traffic arrival rate: %6.2f\n", (float)rightRate/100);
    printf("      traffic light period: %6d\n", rightTime);
    printf("Results (averaged over 100 runs):\n");
    printf("   from left:\n");
    printf("      number of vehicles:   %6.2f\n", leftResults.total/100);
    printf("      average waiting time: %6.2f\n", leftResults.average/100);
    printf("      maximum waiting time: %6.2f\n", leftResults.max/100);
    printf("      clearance time:       %6.2f\n", leftResults.time/100);
    printf("   from right:\n");
    printf("      number of vehicles:   %6.2f\n", rightResults.total/100);
    printf("      average waiting time: %6.2f\n", rightResults.average/100);
    printf("      maximum waiting time: %6.2f\n", rightResults.max/100);
    printf("      clearance time:       %6.2f\n", rightResults.time/100);

    return 0;

}

/* checks if the input string is a positive integer */
int isNumber(char number[]) {

    short i;
    short len = sizeof(*number)/sizeof(number[0]);

    /* checks each character in the string */
    for (i=0; i<len; i++) {
        if (!isdigit(number[i])) {
            return 1;
        }
    }
    return 0;

}