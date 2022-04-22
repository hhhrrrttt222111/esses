// Write a C program to simulate page replacement algorithms
//  a) FIFO 


#include <stdio.h>


void fifo(int pages[], int frames[], int p, int f) {
    printf("\nRef.Str \t|\tFrames\n");
    printf("-------------------------------\n");
    int i, j, k, flag, fault = 0, queue = 0;
    for (i = 0; i < p; ++i) {
        printf("  %d\t\t|\t", pages[i]);
        flag = 0;
        for (j = 0; j < f; ++j) {
            if (frames[j] == pages[i]) {                
                flag = 1;
                printf("   Hit");
                break;
            }
        }
        if (flag == 0) {                             
            frames[queue] = pages[i];
            fault++;
            queue = (queue + 1) % f;               

            for (k = 0; k < f; ++k) {
                printf("%d  ", frames[k]);
            }
        }
        printf("\n");
    }
    printf("Total Page Faults = %d\n", fault);
}

void main() {
    int i, p, f, pages[30], frames[20];
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

    fifo(pages, frames, p, f);

}
