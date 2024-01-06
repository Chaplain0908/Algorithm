#include <iostream>
#include <vector>

using namespace std;

int radix_digit(int x, int i)
{
    return x >> ((4 * i)) & 0xf;
}

void radix_sort(vector<int> &v)
{
    vector<int> aux(v.size());
    for (int i = 0; i < 8; ++i)
    {
        int cnt[16] = {};
        for (int j = 0; j < v.size(); ++j)
        {
            cnt[radix_digit(v[j], i)]++;
        }
        int prev_cnt = cnt[0];
        cnt[0] = 0;
        for (int k = 1; k < 16; ++k)
        {
            int now_cnt = cnt[k];
            cnt[k] = cnt[k - 1] + prev_cnt;
            prev_cnt = now_cnt;
        }
    
        for (int j = 0; j < v.size(); ++j)
        {
            int digit = radix_digit(v[j], i);
            aux[cnt[digit]] = v[j];
            cnt[digit]++;
        }
        for (int j = 0; j < v.size(); ++j)
        {
            v[j] = aux[j];
        }
    }
}

int main()
{
    vector<int> v = {123457, 987543, 3457392, 301830, -485730, 1237493, 2384219};
    radix_sort(v);
    for (int i = 0; i < v.size(); ++i)
    {
        printf("%d ", v[i]);
    }

    system("pause");
    return 0;
}