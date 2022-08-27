#include <stdlib.h>
#include <stdio.h>

struct Vector {
    int *m_pVect;
    int m_nCount;
    int m_nMax;
    int m_nDelta;
};

void
Resize(struct Vector *myVec)
{
    myVec->m_pVect = realloc(myVec->m_pVect, sizeof(int) * (myVec->m_nMax + myVec->m_nDelta));
    myVec->m_nMax += myVec->m_nDelta;
}

void 
Insert(struct Vector *myVec, int elem)
{
    if (myVec->m_nCount == myVec->m_nMax)
        Resize(myVec);
    myVec->m_pVect[myVec->m_nCount++] = elem;
}

void
print(struct Vector myVec)
{
    for (int i = 0; i < myVec.m_nCount; i++) 
        printf("%d ", myVec.m_pVect[i]);
    printf("\n");
}

int
main()
{
    struct Vector mVec;
    mVec.m_nCount = 0;
    mVec.m_nMax = 0;
    mVec.m_nDelta = 10;

    Insert(&mVec, 54);
    Insert(&mVec, 4);
    Insert(&mVec, 5);
    Insert(&mVec, 24);
    Insert(&mVec, 14);
    Insert(&mVec, 58);
    print(mVec);
}
