#include <stdio.h>
#include <string.h>
#include <ctype.h>

char str[100];
int tempCount = 0;

char newTemp()
{
    return 'Z' - tempCount++;
}

int main()
{
    int i, len;
    char left, op1, op2, op;
    char temp;

    printf("\t\tINTERMEDIATE CODE GENERATION\n\n");

    printf("Enter the Expression: ");
    scanf("%99s", str);

    printf("\nThe intermediate code:\n");

    len = strlen(str);

    /* Find assignment operator */
    for (i = 0; i < len; i++)
    {
        if (str[i] == '=')
        {
            left = str[i - 1];
            break;
        }
    }

    /*
       Process * and /
       Example:
       a=b+c*d

       c*d -> Z
    */
    for (i = 0; i < len; i++)
    {
        if (str[i] == '*' || str[i] == '/')
        {
            op = str[i];
            op1 = str[i - 1];
            op2 = str[i + 1];

            temp = newTemp();

            printf("%c := %c %c %c\n",
                   temp, op1, op, op2);

            str[i - 1] = temp;

            /* Remove operator and second operand */
            str[i] = '$';
            str[i + 1] = '$';
        }
    }

    /*
       Process + and -
       Example:
       a=b+Z

       b+Z -> Y
    */
    for (i = 0; i < len; i++)
    {
        if (str[i] == '+' || str[i] == '-')
        {
            op = str[i];

            /* Find left operand */
            int l = i - 1;
            while (l >= 0 && str[l] == '$')
                l--;

            /* Find right operand */
            int r = i + 1;
            while (r < len && str[r] == '$')
                r++;

            op1 = str[l];
            op2 = str[r];

            temp = newTemp();

            printf("%c := %c %c %c\n",
                   temp, op1, op, op2);

            str[l] = temp;
            str[i] = '$';
            str[r] = '$';
        }
    }

    /* Find final result */
    for (i = 0; i < len; i++)
    {
        if (str[i] == '=')
        {
            int r = i + 1;

            while (r < len && str[r] == '$')
                r++;

            printf("%c := %c\n", left, str[r]);
            break;
        }
    }

    return 0;
}