#ifndef BOTTOMKLIST_H
#define BOTTOMKLIST_H
#include <iostream>
template <typename T, int k>
class BottomKList
{
private:
    T *arr[k];

public:
    BottomKList()
    {
        for (int i = 0; i < k; i++)
        {
            arr[i] = nullptr;
        }
    }
    ~BottomKList()
    {
        for (int i = 0; i < k; ++i)
        {
            delete arr[i];
        }
    }

    void addElement(T *element)
    {
        for (int i = 0; i < k; i++)
        {
            if (arr[i] == nullptr)
            {
                arr[i] = element;
                break;
            }
            else
            {
                if (*element < *arr[i])
                {
                    for (int j = k - 1; j > i; j--)
                    {
                        arr[j] = arr[j - 1];
                    }

                    arr[i] = element;
                    break;
                }
            }
        }
    }
    T *getBottomXthElement(int x) const
    {

        if (x >= k || x < 0)
        {
            return nullptr;
        }
        else
        {
            return arr[x];
        }
    }
};
#endif