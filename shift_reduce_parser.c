#include <stdio.h>
#include <string.h>

char ip_sym[30], stack[30];
int ip_ptr = 0, st_ptr = 0;

void check();

int main()
{
    int len;

    printf("\n\t\tSHIFT REDUCE PARSER\n");

    printf("\nGRAMMAR");
    printf("\nE -> E+E");
    printf("\nE -> E*E");
    printf("\nE -> E/E");
    printf("\nE -> a/b");

    printf("\n\nEnter the input symbol: ");
    scanf("%29s", ip_sym);

    len = strlen(ip_sym);

    printf("\n\t\tSTACK IMPLEMENTATION TABLE");
    printf("\n\nStack\t\tInput Symbol\t\tAction");
    printf("\n--------------------------------------------------");

    printf("\n$\t\t%s$\t\t\t--", ip_sym);

    while (ip_ptr < len)
    {
        /* SHIFT */
        stack[st_ptr] = ip_sym[ip_ptr];
        st_ptr++;
        stack[st_ptr] = '\0';

        ip_ptr++;

        printf("\n$%s\t\t%s$\t\t\tSHIFT %c",
               stack, &ip_sym[ip_ptr], stack[st_ptr - 1]);

        /* REDUCE */
        check();
    }

    /* Try final reduction */
    check();

    if (strcmp(stack, "E") == 0 && ip_ptr == len)
    {
        printf("\n$%s\t\t$\t\t\tACCEPT", stack);
    }
    else
    {
        printf("\n$%s\t\t$\t\t\tREJECT", stack);
    }

    printf("\n");

    return 0;
}

void check()
{
    int changed = 1;

    while (changed)
    {
        changed = 0;

        /* E -> a */
        if (st_ptr >= 1 &&
            stack[st_ptr - 1] == 'a')
        {
            stack[st_ptr - 1] = 'E';
            stack[st_ptr] = '\0';

            printf("\n$%s\t\t%s$\t\t\tE->a",
                   stack, &ip_sym[ip_ptr]);

            changed = 1;
            continue;
        }

        /* E -> b */
        if (st_ptr >= 1 &&
            stack[st_ptr - 1] == 'b')
        {
            stack[st_ptr - 1] = 'E';
            stack[st_ptr] = '\0';

            printf("\n$%s\t\t%s$\t\t\tE->b",
                   stack, &ip_sym[ip_ptr]);

            changed = 1;
            continue;
        }

        /* E -> E+E */
        if (st_ptr >= 3 &&
            stack[st_ptr - 3] == 'E' &&
            stack[st_ptr - 2] == '+' &&
            stack[st_ptr - 1] == 'E')
        {
            st_ptr -= 2;
            stack[st_ptr - 1] = 'E';
            stack[st_ptr] = '\0';

            printf("\n$%s\t\t%s$\t\t\tE->E+E",
                   stack, &ip_sym[ip_ptr]);

            changed = 1;
            continue;
        }

        /* E -> E*E */
        if (st_ptr >= 3 &&
            stack[st_ptr - 3] == 'E' &&
            stack[st_ptr - 2] == '*' &&
            stack[st_ptr - 1] == 'E')
        {
            st_ptr -= 2;
            stack[st_ptr - 1] = 'E';
            stack[st_ptr] = '\0';

            printf("\n$%s\t\t%s$\t\t\tE->E*E",
                   stack, &ip_sym[ip_ptr]);

            changed = 1;
            continue;
        }

        /* E -> E/E */
        if (st_ptr >= 3 &&
            stack[st_ptr - 3] == 'E' &&
            stack[st_ptr - 2] == '/' &&
            stack[st_ptr - 1] == 'E')
        {
            st_ptr -= 2;
            stack[st_ptr - 1] = 'E';
            stack[st_ptr] = '\0';

            printf("\n$%s\t\t%s$\t\t\tE->E/E",
                   stack, &ip_sym[ip_ptr]);

            changed = 1;
            continue;
        }
    }
}