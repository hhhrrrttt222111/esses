#include <stdio.h>


void main() {
    int i, j, min, AT[100], WT[100], TAT[100], BT[100], CT[100], temp ; 

    float n, sumct=0, sumtat=0, sumwt=0, avgwt, avgtat ;
    printf ("Enter the no of process: ");
    scanf ("%f", &n);
    printf ("Enter the arrival time: \n");

    for(i = 0;i < n; i++) {
        scanf("%d", &AT[i]);
    }

    printf ("Enter the burst time: \n");

    for(i = 0;i < n; i++) {
        scanf("%d", &BT[i]);
    }

    for (i=0; i<n-1; i++) {         
        for(j=0; j<n-i-1; j++) {
            if ( AT[j] > AT[j+1]) {
                temp = AT[j+1];
                min = BT[j+1];
                AT[j+1] = AT[j];
                BT[j+1] = BT[j];
                AT[j] = temp;
                BT[j] = min;
            }
        }
    }

    for (i=0; i<n; i++) {    
        CT[i] = BT[i]+sumct;
        sumct = sumct+BT[i];
    }

    for (i = 0;i < n; i++) {    
        TAT[i] = CT[i] - AT[i];
        WT[i]=TAT[i]-BT[i];
    }

    for (i = 0;i < n;i++ ) { 
        sumtat = sumtat + TAT[i];
        sumwt = sumwt+WT[i];
    }

    avgtat = sumtat / n;
    avgwt = sumwt/n;
    printf("Average turnaround time = %f \n" , avgtat);
    printf("Average waiting time = %f \n", avgwt); 
}
