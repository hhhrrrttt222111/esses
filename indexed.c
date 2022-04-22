// INDEXED FILE ALLOCATION

#include<stdio.h>

void main() {
    int n, m[20], i, j, sb[20], s[20], b[20][20], x; 

    printf("\nEnter no. of files: "); 
    scanf("%d", &n); 

    for(i=0; i<n; i++) { 
        printf("\nEnter starting block and size of file %d: ", i+1); 
        scanf("%d%d", &sb[i], &s[i]); 

        printf("Enter no. of blocks occupied by file %d: ", i+1); 
        scanf("%d", &m[i]); 

        printf("Enter blocks of file %d: ", i+1); 
        for(j=0; j<m[i]; j++)
            scanf("%d", &b[i][j]); 
    } 

    printf("\nFile\t Index\tLength\n"); 
    for(i=0; i<n; i++) {
        printf("%d\t%d\t%d\n", i+1, sb[i], m[i]); 
    }

    printf("\nEnter file name: "); 
    scanf("%d", &x); 

    printf("File name: %d\n", x);
    i = x-1; 
    printf("Index: %d", sb[i]); 
    printf("\nBlocks occupied are: "); 
    for(j=0; j<m[i]; j++)
        printf("%3d", b[i][j]); 

} 