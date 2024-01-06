#include <iostream>
#include <vector>
using namespace std;

void partition(vector<int> &v)
{
    int i = 1;
    int j = v.size() - 1;
    while (true)
    {
        while (i < j && v[i] < v[0])
        {
            ++i;
        }
        while (i < j && v[0] < v[j])
        {
            --j;
        }
        if(i == j){
            break;
        }
        swap(v[i], v[j]);
    }
    if(v[i] < v[0]){
        swap(v[0], v[i]);
    }else{
        swap(v[0], v[i-1]);
    }
}

int main()
{
    vector<int> v={8, 1, 6, 9, 2, 4, 6, 10, 8, 12, 18, 15, 7};
    partition(v);
    for(int i = 0; i < v.size(); ++i){
        cout << v[i] << " ";
    }
    system("pause");
    return 0;
}