#include <iostream>
#include <stdlib.h>

class CVector
{
    private:
        int *m_pVect; 
        int m_nCount; 
        int m_nMax;
        int m_nDelta; 
        void Init(int delta); 
        void Resize(); 
                       
    public:
        CVector(int delta = 10);
        void print();
        void Insert(int elem); 
        
};

void 
CVector::Insert(int elem)
{
    if(m_nCount == m_nMax ) 
        Resize(); 
    m_pVect[m_nCount++] = elem; 
}

void
CVector::Resize()
{
    m_pVect = (int*) realloc(m_pVect, sizeof(int) * (m_nCount + m_nDelta));
    m_nMax += m_nDelta;
}

void
CVector::print()
{
    for (int i = 0; i < m_nCount; i++)
        std::cout << m_pVect[i] << " ";
    std::cout << std::endl;
}

CVector::CVector(int a)
{
    m_nDelta = a;
    m_nCount = 0;
    m_nMax = 0;
}

int
main()
{
    CVector mVec;

    mVec.Insert(54);
    mVec.Insert(74);
    mVec.Insert(84);
    mVec.Insert(54);
    mVec.Insert(14);
    mVec.Insert(4);
    mVec.print();
}
