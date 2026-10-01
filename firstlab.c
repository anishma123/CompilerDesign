#include <stdio.h>
#include <string.h>

int main()
{
    char com[100];
    int i, a = 0;

    printf("\nEnter comment: ");
    fgets(com, sizeof(com), stdin);

    if (com[0] == '/')
    {
        if (com[1] == '/')
        {
            printf("\nIt is a comment");
        }
        else if (com[1] == '*')
        {
            for (i = 2; i < strlen(com) - 1; i++)
            {
                if (com[i] == '*' && com[i + 1] == '/')
                {
                    printf("\nIt is a comment");
                    a = 1;
                    break;
                }
            }

            if (a == 0)
                printf("\nIt is not a comment");
        }
        else
        {
            printf("\nIt is not a comment");
        }
    }
    else
    {
        printf("\nIt is not a comment");
    }

    return 0;
}