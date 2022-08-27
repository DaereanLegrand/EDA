#include <stdlib.h>
#include <stdio.h>

int *gpVect = NULL;
int gnCount = 0;
int gnMax = 0;

void
Resize()
{
    const int delta = 10;
    gpVect = realloc(gpVect, sizeof(int) * (gnMax + delta));
    gnMax += delta;
}

void 
Insert(int elem)
{
    if (gnCount == gnMax)
        Resize();
    gpVect[gnCount++] = elem;
}

void
print()
{
    for (int i = 0; i < gnCount; i++) 
        printf("%d ", gpVect[i]);
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
