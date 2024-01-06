#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int> &v, int begin, int mid, int end, vector<int> a)
{
    int i = begin;
    int j = mid;
    int k = 0;
    while (i < mid && j < end)
    {
        if (v[i] < v[j])
        {
            a[k] = v[i];
            ++k;
            ++i;
        }
        else
        {
            a[k] = v[j];
            ++k;
            ++j;
        }
    }
    while (i < mid)
    {
        a[k] = v[i];
        ++k;
        ++i;
    }
    while (j < end)
    {
        a[k] = v[j];
        ++k;
        ++j;
    }

    for (int i = 0; i < k; ++i)
    {
        v[begin + i] = a[i];
    }
}

void merge_sort_helper(vector<int> &v, int begin, int end, vector<int> &a)
{
    // cout << begin << " " << end << endl;
    int n = end - begin;
    if (n == 0 || n == 1)
    {
        return;
    }
    int halfn = n / 2;
    int mid = begin + halfn;
    merge_sort_helper(v, begin, mid, a);
    merge_sort_helper(v, mid, end, a);
    merge(v, begin, mid, end, a);
}

void merge_sort(vector<int>& v){
    vector<int> a(v.size());
    merge_sort_helper(v, 0, v.size(), a);
}

int main()
{
    vector<int> v = {9, 4, 8, 2, 1, 6, 0, 3, 5, 7};
    merge_sort(v);
    for (int i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " ";
    }
    system("pause");
    return 0;
}