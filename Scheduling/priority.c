#include <stdio.h>

int i, j, n;
float TATAvg, WTAvg;

struct Process {
    int pId;
    int bt;
    int priority;
};

void read(struct Process p[]) {
    printf("\n");
    for (i = 0; i < n; ++i) {
        p[i].pId = i + 1;
        printf("Enter burst time for process %d: ", p[i].pId);
        scanf("%d", &p[i].bt);
        printf("Enter the priority: ");
        scanf("%d", &p[i].priority);
    }
}

void display(struct Process p[], int WT[], int TAT[]) {
    printf("\nProcessID | BurstTime | Priority | Waiting time | Turn Around Time\n");
    for (i = 0; i < n; ++i) {
        printf("%d\t\t%d\t%d\t\t%d\t\t%d\n", p[i].pId, p[i].bt, p[i].priority, WT[i], TAT[i]);
    }
    printf("Average waiting time: %f", WTAvg);
    printf("\nAverage turnaround time: %f", TATAvg);
    printf("\n");
}

void sort(struct Process p[]) {
    struct Process temp;
    for (i = 0; i < n - 1; ++i) {
        for (j = 0; j < n - 1 - i; ++j) {
            if (p[j].priority > p[j + 1].priority) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void findWaitingTime(struct Process p[], int WT[]) {
    WT[0] = 0;
    int WTSum = 0;
    for (i = 1; i < n; ++i) {
        WT[i] = WT[i - 1] + p[i - 1].bt;
        WTSum += WT[i];
    }
    WTAvg = (float)WTSum / n;
}

void findTurnAroundtime(struct Process p[], int TAT[], int WT[]) {
    int TATSum = 0;
    for (i = 0; i < n; ++i) {
        TAT[i] = p[i].bt + WT[i];
        TATSum += TAT[i];
    }
    TATAvg = (float)TATSum / n;
}

void main() {
    struct Process p[20];      
    int WT[20], TAT[20];
    printf("Enter no. of Processes: ");
    scanf("%d", &n);
    read(p);
    sort(p);
    findWaitingTime(p, WT);
    findTurnAroundtime(p, TAT, WT);
    display(p, WT, TAT);
}