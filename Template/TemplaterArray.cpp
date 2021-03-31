#include<iostream>
#include<cstring>
typedef unsigned int uint32;
typedef int int32;
template<class T>
class CArry
{
    private:
        uint32 size;
        T *ptr;
    public:
        CArry(int = 0);
        ~CArry();
        CArry(const CArry &);
        T Push(const T &);
        T GetLength()const;
        CArry<T>& operator=(const CArry<T> &);
        T& operator[](const T &i);
};

template<class T>
CArry<T>::CArry(int s)
{
    if(s < 0)
    {
        std::cerr<<"fault size with negative"<<std::endl;
        return;
    }
    if(s == 0)
    {
        size = 0;
        ptr = nullptr;
    }
    else
    {
        size = s;
        ptr = new T(size);
    }
}

template<class T>
CArry<T>::~CArry()
{
    delete []ptr;
}

template<class T>
CArry<T>::CArry(const CArry<T> &carry)
{
    if (!carry.ptr)
    {
        this->ptr = nullptr;
        this->size = 0;
        return;
    }
    this->ptr = new T(carry.size);
    memcpy(this->ptr,carry.ptr,sizeof(T)*carry.size);
}

template<typename T>
T CArry<T>::Push(const T &i)
{
    if(ptr)
    {
        T *tmpPtr = new T(size + 1);
        std::memcpy(tmpPtr,ptr,sizeof(T)*size);
        //tmpPtr[size++] = i;
        delete []ptr;
        ptr = tmpPtr;
    }
    else
    {
        ptr = new T(1);
    }
    ptr[size++] = i;
    //delete tmpPtr; delete the same space here and Distructor function
}

template<class T>
T CArry<T>::GetLength()const
{
    return size;
}

template<class T>
CArry<T>&  CArry<T>::operator=(const CArry<T> &c)
{
    if(this == &c)
        return *this;
    if(!c.ptr)
    {
        if(nullptr != this->ptr)
        {
            delete this->ptr;
        }
        this->ptr = nullptr;
        this->size = 0;
        return *this;
    }
    if(this->ptr)
    {
        delete this->ptr;
    }
    this->ptr = new T(c.size);
    this->size = c.size;
    memcpy(this->ptr,c.ptr,sizeof(T)*c.size);
    return *this;
}

template<class T>
T& CArry<T>::operator[](const T &i)
{
    return ptr[i];
}

/*********************************Test_F********************/

template<typename T>
void ExpectOrder(CArry<T> &c,int32 position,T value)
{
    if(value == c[position-1])
    {
        std::cout<<"expected position "<<position<<" is equal to value "<<value<<std::endl;
        return;
    }
    std::cout<<"expect order is fault"<<std::endl;
}

template<class T>
void ExpectEqual(T source,T destin)
{
    if(source == destin)
    {
        std::cout<<"ExpectEqual is equal"<<std::endl;
        return;
    }
    std::cout<<"ExpectEqual is inequal"<<std::endl;
}
void Test_CopyConstructor()
{
    //source is null
    CArry<int> carry;
    CArry<int> copyArry = carry;
    ExpectEqual(copyArry.GetLength(),0);

    //source is Non-null
    carry.Push(1);
    CArry<int> copyArry1 = carry;
    ExpectEqual(copyArry1.GetLength(),1);
}
void Test_Push()
{
    //test size is right
    CArry<int> carry;
    for(int i = -1;i < 4;i++)
    {
        carry.Push(i);
    }
    ExpectEqual(carry.GetLength(),5);
    //test element whether in order
    ExpectOrder(carry,3,1);
    ExpectOrder(carry,1,-1);
}
void Test_CopyValue()
{
    CArry<int> carry(1);
    carry[0] = 1;
    ExpectEqual(carry[0],1);

}

void Test_operatorAssignment()
{
    CArry<int> carry(3);
    CArry<int> copyArry;
    copyArry = carry;
}


int main()
{
    Test_CopyConstructor();
    Test_Push();
    Test_CopyValue();
    Test_operatorAssignment();
    return 0;
}