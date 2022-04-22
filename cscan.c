// Write a C program to simulate disk scheduling algorithms 
// c) C-SCAN 



#include<stdio.h>
#include<stdlib.h>


void sort(int Arr[20], int n) {
    int i, j, temp;
    for(i=0; i<n-1; i++) {
        for(j=0; j<n-1-i; j++) {
            if(Arr[j] > Arr[j+1]) {
                temp = Arr[j];
                Arr[j] = Arr[j+1];
                Arr[j+1] = temp;
            }
        }
    }
}


void cscan(int Arr[20], int n, int start) {
    int i, pos, diff, seekTime=0, current;

    for(i=0; i<n; i++) {                                      
        if(Arr[i]==start) {
            pos=i;
            break;
        }
    }

    printf("\nMovement of Cylinders\n");
    for(i=pos; i<n-1; i++) {
        diff = abs(Arr[i+1] - Arr[i]);
        seekTime += diff;
        printf("Move from %d to %d with seek time %d\n", Arr[i], Arr[i+1], diff);
    }
    current=0;                                   

    printf("Move from %d to %d with seek time %d\n", Arr[i], current, 0);

    for(i=0; i<pos; i++) {
        diff = abs(Arr[i] - current);
        seekTime += diff;
        printf("Move from %d to %d with seek time %d\n", current, Arr[i], diff);
        current = Arr[i];
    }
    printf("\nTotal Seek Time: %d", seekTime);

    printf("\nAverage Seek Time = %f", (float)seekTime/(n-1));        
    printf("\n");
}


void main() {
    int diskQueue[20], n, start, i, max;

    printf("Enter the size of Queue: ");
    scanf("%d", &n);

    printf("Enter the Queue: ");
    for(i=1;i<=n;i++) {             
        scanf("%d",&diskQueue[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &start);                                
    diskQueue[0] = start;                     
    ++n;
    
    sort(diskQueue, n);                                      
    cscan(diskQueue, n, start);

}



