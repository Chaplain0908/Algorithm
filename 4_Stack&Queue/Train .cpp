#include <iostream>
#include <stack>
#include <vector>

using namespace std;

bool check(const vector<int> &v)
{
    stack<int> st;
    int i = 0;
    int e = 0;
    while (e < v.size())
    {
        if (!st.empty() && st.top() == e)
        {
            st.pop();
            ++e;
            continue;
        }
        if (i != v.size())
        {
            if (v[i] == e)
            {
                ++e;
            }
            else
            {
                st.push(v[i]);
            }
            ++i;
            continue;
        }
        return false;
    }
    return true;
}

int main()
{
    system("pause");
    return 0;
}