// Write a C program to simulate page replacement algorithms
// c) LFU

#include <stdio.h>
void main() {
    int q[20], pages[50], c = 0, c1, d, f, i, j, k = 0, p, r, t, b[20], c2[20];
    printf("Number of Frames: ");
    scanf("%d", &f);
    printf("Number of Pages: ");
    scanf("%d", &p);
    printf("Enter the reference string: ");
    for (i = 0; i < p; i++)
        scanf("%d", &pages[i]);
    q[k] = pages[k];
    printf("\n\t%d\n", q[k]);
    c++;
    k++;
    for (i = 1; i < p; i++) {
        c1 = 0;
        for (j = 0; j < f; j++) {
            if (pages[i] != q[j])
                c1++;
        }
        if (c1 == f) {
            c++;
            if (k < f) {
                q[k] = pages[i];
                k++;
                for (j = 0; j < k; j++)
                    printf("\t%d", q[j]);
                printf("\n");
            }
            else {
                for (r = 0; r < f; r++) {
                    c2[r] = 0;
                    for (j = i - 1; j < p; j--) {
                        if (q[r] != pages[j])
                            c2[r]++;
                        else
                            break;
                    }
                }
                for (r = 0; r < f; r++)
                    b[r] = c2[r];
                for (r = 0; r < f; r++) {
                    for (j = r; j < f; j++) {
                        if (b[r] < b[j]) {
                            t = b[r];
                            b[r] = b[j];
                            b[j] = t;
                        }
                    }
                }
                for (r = 0; r < f; r++) {
                    if (c2[r] == b[0])
                        q[r] = pages[i];
                    printf("\t%d", q[r]);
                }
                printf("\n");
            }
        }
    }

    printf("Total Page Faults = %d\n\n", c);
}