#include <iostream>
#include <vector>
#include <utility>
#include <math.h>
using namespace std;

vector<int> merge(const vector<int> &a, const vector<int> &b)
{
    vector<int> result;
    int i = 0;
    int j = 0;
    while(i < a.size() && j < b.size())
    {
        if (a[i] < b[j])
        {
            result.push_back(a[i]);
            ++i;
        }
        else
        {
            result.push_back(b[j]);
            ++j;
        }
    }
    while (i < a.size())
    {
        result.push_back(a[i]);
        ++i;
    }
    while (j < b.size())
    {
        result.push_back(b[j]);
        ++j;
    }

    return result;
}

int main()
{
    vector<int> v1 = {3, 4, 6, 8, 9, 10, 12, 14, 15, 16};
    vector<int> v2 = {0, 1, 2, 5, 7, 11, 13};
    vector<int> result = merge(v1, v2);
    for (int i = 0; i < result.size(); ++i)
    {
        cout << result[i] << " ";
    }
    system("pause");
    return 0;
}