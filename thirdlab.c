#include <stdio.h>
#include <ctype.h>

int main()
{
    char a[100];
    int flag = 1, i = 1;

    printf("\nEnter an identifier: ");
    fgets(a, sizeof(a), stdin);

    if (isalpha(a[0]) || a[0] == '_')
        flag = 1;
    else
        flag = 0;

    while (a[i] != '\0' && a[i] != '\n')
    {
        if (!isdigit(a[i]) && !isalpha(a[i]) && a[i] != '_')
        {
            flag = 0;
            break;
        }
        i++;
    }

    if (flag == 1)
        printf("\nValid identifier");
    else
        printf("\nNot a valid identifier");

    return 0;
}