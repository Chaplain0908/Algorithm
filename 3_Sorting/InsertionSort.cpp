#include <iostream>
#include <vector>
#include <utility>
#include <math.h>
using namespace std;

int main()
{
    vector<int> v = {4, 9, 8, 3, 6, 2, 1, 5, 0, 7};
    for (int i = 1; i < v.size(); ++i)
    {
        int j = 0;
        int temp = v[i];
        for (j = i - 1; j >= 0; --j)
        {
            if (v[j] > temp)
            {
                v[j + 1] = v[j];
            }
            else
            {
                break;
            }
        }
        v[j+1] = temp;
    }

    for (int i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " ";
    }

    system("pause");
    return 0;
}