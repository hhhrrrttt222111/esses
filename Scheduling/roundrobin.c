#include <stdio.h>

int i, n, quantum; 

void read(int b[]) {
    for (i = 0; i < n; ++i) {
        printf("Enter burst time of process %d: ", i);
        scanf("%d", &b[i]);
    }
}

void findWaitingtime(int b[], int WT[]) {
    int b_rem[20];
    for (i = 0; i < n; ++i) {
        b_rem[i] = b[i];                  
    }
    int time = 0;

    while (1) {

        int flag = 0;

        for (i = 0; i < n; ++i) {

            if (b_rem[i] > 0) {
                flag = 1;   
                if (b_rem[i] > quantum) {
                    time += quantum;             
                    b_rem[i] -= quantum;        
                }
                else {                         
                    time += b_rem[i];          
                    WT[i] = time - b[i];      
                    b_rem[i] = 0;              
                }
            }
        }
        if (flag == 0) {                    
            break;
        }
    }
}

void findTurnAroundtime(int TAT[], int b[], int WT[]) {
    for (i = 0; i < n; ++i) {
        TAT[i] = b[i] + WT[i];
    }
}

void display(int b[], int WT[], int TAT[]) {
    int WTSum = 0, TATSum = 0;
    printf("Process\tBurstTime WaitingTime  TurnAroundTime\n");
    for (i = 0; i < n; ++i) {
        WTSum += WT[i];
        TATSum += TAT[i];
        printf("%d\t%d\t\t%d\t%d\n", i, b[i], WT[i], TAT[i]);
    }
    printf("Average waiting time: %f", (float)WTSum / n);
    printf("\nAverage turnaround time: %f", (float)TATSum / n);
    printf("\n");
}

void calcTime(int b[], int WT[], int TAT[]) {
    findWaitingtime(b, WT);
    findTurnAroundtime(TAT, b, WT);
    display(b, WT, TAT);
}

void main() {
    int b[20], TAT[20], WT[20];
    printf("Enter no. of Processes: ");
    scanf("%d", &n);
    read(b);
    printf("Enter time quantum: ");
    scanf("%d", &quantum);
    calcTime(b, WT, TAT);
}