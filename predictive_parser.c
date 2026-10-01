#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char s[20], stack[20];

int main()
{
    // LL(1) parsing table
    // e = E, b = B, t = T, c = C, f = F
    // n = epsilon (ε)
    char m[5][6][4] = {
        {"tb", "", "", "tb", "", ""},
        {"", "+tb", "", "", "n", "n"},
        {"fc", "", "", "fc", "", ""},
        {"", "n", "*fc", "", "n", "n"},
        {"i", "", "", "(e)", "", ""}
    };

    // Length of each production
    int size[5][6] = {
        {2, 0, 0, 2, 0, 0},
        {0, 3, 0, 0, 1, 1},
        {2, 0, 0, 2, 0, 0},
        {0, 1, 3, 0, 1, 1},
        {1, 0, 0, 3, 0, 0}
    };

    int i, j, k, n;
    int str1, str2;

    printf("\nEnter the input string: ");
    scanf("%19s", s);

    strcat(s, "$");
    n = strlen(s);

    // Initialize stack
    stack[0] = '$';
    stack[1] = 'e';

    i = 1;
    j = 0;

    printf("\nStack\t\tInput\n");
    printf("--------------------------\n");

    while (stack[i] != '$')
    {
        // If stack top matches input symbol
        if (stack[i] == s[j])
        {
            i--;
            j++;

            // Display stack
            for (k = 0; k <= i; k++)
                printf("%c", stack[k]);

            printf("\t\t");

            // Display remaining input
            for (k = j; k < n; k++)
                printf("%c", s[k]);

            printf("\n");

            continue;
        }

        // Find row according to stack symbol
        switch (stack[i])
        {
            case 'e':
                str1 = 0;
                break;

            case 'b':
                str1 = 1;
                break;

            case 't':
                str1 = 2;
                break;

            case 'c':
                str1 = 3;
                break;

            case 'f':
                str1 = 4;
                break;

            default:
                printf("\nERROR\n");
                return 1;
        }

        // Find column according to input symbol
        switch (s[j])
        {
            case 'i':
                str2 = 0;
                break;

            case '+':
                str2 = 1;
                break;

            case '*':
                str2 = 2;
                break;

            case '(':
                str2 = 3;
                break;

            case ')':
                str2 = 4;
                break;

            case '$':
                str2 = 5;
                break;

            default:
                printf("\nERROR\n");
                return 1;
        }

        // Empty table entry = ERROR
        if (m[str1][str2][0] == '\0')
        {
            printf("\nERROR\n");
            return 1;
        }

        // Epsilon production
        else if (m[str1][str2][0] == 'n')
        {
            i--;
        }

        // Terminal i
        else if (m[str1][str2][0] == 'i')
        {
            stack[i] = 'i';
        }

        // Push production into stack
        else
        {
            for (k = size[str1][str2] - 1; k >= 0; k--)
            {
                stack[i] = m[str1][str2][k];
                i++;
            }

            i--;
        }

        // Display stack
        for (k = 0; k <= i; k++)
            printf("%c", stack[k]);

        printf("\t\t");

        // Display remaining input
        for (k = j; k < n; k++)
            printf("%c", s[k]);

        printf("\n");
    }

    // Final check
    if (stack[i] == '$' && s[j] == '$')
        printf("\nSUCCESS\n");
    else
        printf("\nERROR\n");

    return 0;
}