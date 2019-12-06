#include <stdlib.h>
#include <stdio.h>

int usage(char *name){
    printf("%s stop\n", name);
    printf("%s start stop\n", name);
    printf("%s start step stop\n", name);
    return(1);
}

int main(int argc, char **argv){
    int i;
    int max;
    int step;
    // We behave differently based on the number of positional argument received
    switch (argc){
        // we only received the stop
        case 2:
            i = 1;
            max = atoi(argv[1]);
            step = 1;
            break;
        // we received the start and the stop
        case 3:
            i = atoi(argv[1]);
            max = atoi(argv[2]);
            step = 1;
            break;
        // we received the start, the step, and the stop
        case 4:
            i = atoi(argv[1]);
            step = atoi(argv[2]);
            max = atoi(argv[3]);
            break;
        default:
            return(usage(argv[0]));
    }
    // generate the sequence if start is less than stop and the step is positive
    if ((i <= max) && (step > 0)){
        while (i <= max){
            printf("%d\n", i);
            i = i + step;
        }
    }
    return(0);
}
