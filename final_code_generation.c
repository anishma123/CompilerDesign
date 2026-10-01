#include <stdio.h>
#include <string.h>

char op[10], arg1[10], arg2[10], result[10];
int main()
{
    FILE *fp1, *fp2;

    fp1 = fopen("input.txt", "r");
    fp2 = fopen("output.txt", "w");

    if (fp1 == NULL)
    {
        printf("Error: Cannot open input.txt\n");
        return 1;
    }

    if (fp2 == NULL)
    {
        printf("Error: Cannot create output.txt\n");
        fclose(fp1);
        return 1;
    }

    /*
       Read intermediate code from input.txt

       Format:
       operator operand1 operand2 result

       Example:
       * c d Z
       + b Z Y
       = Y - a
    */

    while (fscanf(fp1, "%9s %9s %9s %9s",
                  op, arg1, arg2, result) == 4)
    {
        if (strcmp(op, "+") == 0)
        {
            fprintf(fp2, "\nMOV R0, %s", arg1);
            fprintf(fp2, "\nADD R0, %s", arg2);
            fprintf(fp2, "\nMOV %s, R0", result);
        }

        else if (strcmp(op, "*") == 0)
        {
            fprintf(fp2, "\nMOV R0, %s", arg1);
            fprintf(fp2, "\nMUL R0, %s", arg2);
            fprintf(fp2, "\nMOV %s, R0", result);
        }

        else if (strcmp(op, "-") == 0)
        {
            fprintf(fp2, "\nMOV R0, %s", arg1);
            fprintf(fp2, "\nSUB R0, %s", arg2);
            fprintf(fp2, "\nMOV %s, R0", result);
        }

        else if (strcmp(op, "/") == 0)
        {
            fprintf(fp2, "\nMOV R0, %s", arg1);
            fprintf(fp2, "\nDIV R0, %s", arg2);
            fprintf(fp2, "\nMOV %s, R0", result);
        }

        else if (strcmp(op, "=") == 0)
        {
            fprintf(fp2, "\nMOV R0, %s", arg1);
            fprintf(fp2, "\nMOV %s, R0", result);
        }
    }

    fclose(fp1);
    fclose(fp2);

    printf("Final code generated successfully.\n");
    printf("Check output.txt for the generated code.\n");

    return 0;
}