
#include <stdio.h>

int i, j, n, pId[20];
float TATAvg, WTAvg;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sort(int b[]) {
    for (i = 0; i < n - 1; ++i) {
        for (j = 0; j < n - 1 - i; ++j) {
            if (b[j] > b[j + 1]) {
                swap(&b[j], &b[j + 1]);
                swap(&pId[j], &pId[j + 1]);
            }
        }
    }
}

void read(int b[]) {
    for (i = 0; i < n; ++i) {
        printf("Enter burst time of process %d: ", i);
        scanf("%d", &b[i]);
        pId[i] = i + 1; 
    }
    sort(b);
}

void findWaitingtime(int b[], int WT[]) {
    WT[0] = 0;
    int WTSum = 0;
    for (i = 1; i < n; ++i) {
        WT[i] = WT[i - 1] + b[i - 1];
        WTSum += WT[i];
    }
    WTAvg = (float)WTSum / n;
}

void findTurnAroundtime(int TAT[], int b[], int WT[]) {
    int TATSum = 0;
    for (i = 0; i < n; ++i) {
        TAT[i] = b[i] + WT[i];
        TATSum += TAT[i];
    }
    TATAvg = (float)TATSum / n;
}

void display(int b[], int WT[], int TAT[]) {
    printf("Process\tBurstTime WaitingTime  TurnAroundTime\n");
    for (i = 0; i < n; ++i) {
        printf("%d\t%d\t\t%d\t%d\n", pId[i], b[i], WT[i], TAT[i]);
    }
    printf("Average waiting time: %f", WTAvg);
    printf("\nAverage turnaround time: %f", TATAvg);
    printf("\n");
}

void calcTime(int b[]) {
    int WT[20], TAT[20];
    findWaitingtime(b, WT);
    findTurnAroundtime(TAT, b, WT);
    display(b, WT, TAT);
}

void main() {
    int b[20];
    printf("Enter no: of Processes: ");
    scanf("%d", &n);
    read(b);
    calcTime(b);
}