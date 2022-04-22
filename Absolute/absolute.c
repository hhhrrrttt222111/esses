// Absolute loader

#include<stdio.h>
#include<stdlib.h>


void main() {
    char ch;
    int i,n;
    FILE *f1;
    f1 = fopen("in.txt","r");
    ch = fgetc(f1);

    if(ch == 'H') {
        ch = fgetc(f1);
        while(ch!= '\0') {
            if(ch == '^') {
                ch = fgetc(f1);
                continue;
            }
            printf("\nName of the Program: ");
            while(ch!='^') {
                printf("%c",ch);
                ch = fgetc(f1);
            }
            printf("\nStarting address of the program: ");
            ch = fgetc(f1);
            
            while(ch!='^') {
                printf("%c",ch);
                ch = fgetc(f1);
            }

            printf("\nLength of the program: ");
            ch = fgetc(f1);

            while(ch!='T') {
                printf("%c",ch);
                ch = fgetc(f1);
            }

            ch = fgetc(f1);
            ch = fgetc(f1);
            printf("\n\nText Object Codes: \n");

            while(ch!='E') {
                printf("%c",ch);
                ch = fgetc(f1);
                if(ch == '^')
                {
                ch = fgetc(f1);
                printf("\n");
                continue;
                }
            }
            break;
        }
    }
}
