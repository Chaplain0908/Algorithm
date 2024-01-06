#include <iostream>
#include <string>
#include <stack>
using namespace std;

int rank_(char c)
{
    switch (c)
    {
        case '{':
        case '}':
        {
            return 3;
        }

        case '[':
        case ']':
        {
            return 2;
        }

        case '(':
        case ')':
        {
            return 1;
        }
    }
}

bool check(const string &s)
{
    stack<char> st;
    for (int i = 0; i < s.size(); ++i)
    {
        switch (s[i])
        {
            case '{':
            case '[':
            case '(':
            {
                if (!st.empty() && rank_(st.top()) < rank_(s[i]))
                {
                    return false;
                }
                st.push(s[i]);
                break;
            }

            case '}':
            case ']':
            case ')':{
                if(st.empty() && rank_(st.top()) != rank_(s[i])){
                    return false;
                }
                st.pop();
                break;
            }
        }
    }
    return st.empty();
}

int main()
{
    string s;
    cin >> s;
    cout << check(s) << endl;
    
    system("pause");
    return 0;
}