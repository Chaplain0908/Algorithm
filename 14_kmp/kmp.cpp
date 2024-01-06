#include<iostream>
#include<string>
#include<vector>

using namespace std;

vector<int> getNext(string const &s){
    vector<int> v = {0};
    int j = 0;
    for(int i = 1; i < s.size(); ){
        if(s[i] != s[j]){
            if(j == 0){
                v.push_back(0);
                ++i;
            }else{
                j = v[j-1];
            }
        }else{
            v.push_back(j+1);
            ++i;
            ++j;
        }
    }
    return v;
}

int main(){
    string s = "abcaabcabc";
    vector<int> next = getNext(s);
    for(int i = 0; i < next.size(); ++i){
        cout << next[i] << " ";
    }
    cout << endl;
    system("pause");
    return 0;
}