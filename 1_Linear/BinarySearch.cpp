#include <iostream>

using namespace std;

int BS(int *a, int begin, int end, int target)
{
    int n = end - begin;
    if (n == 0)
    {
        return -1;
    }
    int mid = begin + n / 2;
    if (target < a[mid])
    {
        return BS(a, begin, mid, target);
    }
    else if (target > a[mid])
    {
        return BS(a, mid + 1, end, target);
    }
    else
    {
        return mid;
    }
}

int BS(int *a, int begin, int end, int target)
{
    while (true)
    {
        int n = end - begin;
        if (n == 0)
        {
            return -1;
        }
        int mid = begin + n / 2;
        if (target < a[mid])
        {
            end = mid;
        }
        else if (target > a[mid])
        {
            begin = mid + 1;
        }
        else
        {
            return mid;
        }
    }
}
