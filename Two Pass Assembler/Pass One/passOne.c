#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main() {
    FILE *F1, *F2, *F3;
    int lc, sa, l, op1, o, len;
    char m1[20], la[20], op[20], otp[20];

    F1 = fopen("input.txt", "r");
    F3 = fopen("symtab.txt", "w");
    fscanf(F1, "%s %s %d", la, m1, &op1);

    if (strcmp(m1, "START") == 0) {
        sa = op1;
        lc = sa;
        printf("\t%s\t%s\t%d\n", la, m1, op1);
    }
    else
        lc = 0;

    fscanf(F1, "%s %s", la, m1);

    while (!feof(F1)) {
        fscanf(F1, "%s", op);
        printf("\n%d\t%s\t%s\t%s\n", lc, la, m1, op);
        if (strcmp(la, "-") != 0) {
            fprintf(F3, "\n%d\t%s\t%s\t%s\n", lc, la, m1, op);
        }
        F2 = fopen("optab.txt", "r");
        fscanf(F2, "%s %d", otp, &o);
        while (!feof(F2)) {
            if (strcmp(m1, otp) == 0) {
                lc = lc + 3;
                break;
            }
            fscanf(F2, "%s %d", otp, &o);
        }

        fclose(F2);
        if (strcmp(m1, "WORD") == 0) {
            lc = lc + 3;
        }

        else if (strcmp(m1, "RESW") == 0) {
            op1 = atoi(op);
            lc = lc + (3 * op1);
        }

        else if (strcmp(m1, "BYTE") == 0) {
            if (op[0] == 'X')
                lc = lc + 1;
            else
            {
                len = strlen(op) - 3;
                lc = lc + len;
            }
        }

        else if (strcmp(m1, "RESB") == 0) {
            op1 = atoi(op);
            lc = lc + op1;
        }
        fscanf(F1, "%s%s", la, m1);
    }

    if (strcmp(m1, "END") == 0) {
        printf("\nProgram Length = %d", lc - sa);
    }
    
    fclose(F1);
    fclose(F3);
}