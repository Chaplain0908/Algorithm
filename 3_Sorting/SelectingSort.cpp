#include <iostream>
#include <vector>
#include <utility>
#include <math.h>
using namespace std;

int main()
{
    vector<int> v = {4, 9, 8, 3, 6, 2, 1, 5, 0, 7};
    for (int i = 0; i < v.size() - 1; ++i)
    {
        int min_idx = i;
        for (int j = i + 1; j < v.size(); ++j)
        {
            if (v[j] < v[min_idx])
            {
                min_idx = j;
            }
        }
        swap(v[i], v[min_idx]);
    }
    for (int i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " ";
    }

    system("pause");
    return 0;
}