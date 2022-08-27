#include <stdlib.h>
#include <stdio.h>

int gVect[100];
int gnCount = 0;

void 
Insert(int elem)
{
    if (gnCount < 100)
        gVect[gnCount++] = elem;
}

void
print()
{
    for (int i = 0; i < gnCount; i++) 
        printf("%d ", gVect[i]);
    printf("\n");
}

int
main()
{
    Insert(45);
    Insert(5);
    Insert(4);
    Insert(87);
    Insert(21);
    Insert(43);

    print();
}
