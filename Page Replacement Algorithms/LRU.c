// Write a C program to simulate page replacement algorithms
// b) LRU


#include <stdio.h>

int findLRU(int time[], int f) {
    int k, min, pos;
    pos = 0;
    min = time[0];
    for (k = 1; k < f; ++k) {
        if (time[k] < min) {
            min = time[k];
            pos = k;
        }
    }
    return pos;
}


void LRU(int pages[], int frames[], int time[], int f, int p) {
    printf("\nRef.Str \t|\tFrames\n");
    printf("-------------------------------\n");

    int i, j, k, pos, flag, fault, counter, queue;
    counter = 0, queue = 0, fault = 0;

    for (i = 0; i < p; ++i) {
        flag = 0;
        printf("  %d\t\t|\t", pages[i]);

        for (j = 0; j < f; ++j) {
            if (frames[j] == pages[i]) {
                flag = 1;                            
                counter++;
                time[j] = counter;                        
                printf("   Hit\n");
                break;
            }
        }

        if ((flag == 0) && (queue < f)) {             
            fault++;
            counter++;
            frames[queue] = pages[i];
            time[queue] = counter;
            queue++;                                   
        }

        else if ((flag == 0) && (queue == f)) {      
            fault++;
            counter++;
            pos = findLRU(time, f);
            frames[pos] = pages[i];
            time[pos] = counter;
        }

        if (flag == 0) {
            for (k = 0; k < f; ++k) {
                printf("%d  ", frames[k]);
            }
            printf("\n");
        }
    }
    printf("Total Page Faults = %d\n\n", fault);
}



void main() {
    int i, p, f, pages[30], frames[20], time[20];
    printf("Number of Frames: ");
    scanf("%d", &f);

    for (i = 0; i < f; ++i) {
        frames[i] = -1;
    }
    printf("Number of Pages: ");
    scanf("%d", &p);
    printf("Enter the reference string: ");
    for (i = 0; i < p; ++i) {
        scanf("%d", &pages[i]);
    }
    LRU(pages, frames, time, f, p);

}

