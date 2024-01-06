#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int> &v, int begin, int end)
{
    int i = begin + 1;
    int j = end - 1;
    while (true)
    {
        while (i < j && v[i] < v[begin])
        {
            ++i;
        }
        while (i < j && v[begin] < v[j])
        {
            --j;
        }
        if (i == j)
        {
            break;
        }
        swap(v[i], v[j]);
    }
    if (v[i] < v[begin])
    {
        swap(v[begin], v[i]);
        return i;
    }
    else
    {
        swap(v[begin], v[i - 1]);
        return i - 1;
    }
}

void quick_sort_helper(vector<int> &v, int begin, int end)
{
    int n = end - begin;
    if (n == 0 || n == 1)
    {
        return;
    }
    int p = partition(v, begin, end);
    quick_sort_helper(v, begin, p);
    quick_sort_helper(v, p + 1, end);
}

void quick_sort_helper2(vector<int> &v, int begin, int end)
{
    while (begin != end && begin+1 != end)
    {
        int p = partition(v, begin, end);
        quick_sort_helper2(v, begin, p);
        begin = p + 1;
    }
}

void quick_sort(vector<int> &v)
{
    quick_sort_helper(v, 0, v.size());
}

int main()
{
    vector<int> v = {9, 3, 2, 7, 4, 1, -3, 5, -9, 32, -1};
    quick_sort(v);
    for (int i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " ";
    }
    system("pause");
    return 0;
}
// 随机
// 三点取中
// 九点取中